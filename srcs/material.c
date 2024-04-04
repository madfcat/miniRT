#include "miniRT.h"

t_material create_material(t_color albedo, double fuzz, t_scatter scatter)
{
	t_material mat;

	mat.albedo = albedo;
	if (fuzz < 1)
		mat.fuzz = fuzz;
	else
		mat.fuzz = 1;
	mat.scatter = scatter;
	return (mat);
}

void	init_material(t_material *mat, t_material mat2)
{
	mat->albedo = mat2.albedo;
	mat->fuzz = mat2.fuzz;
	mat->scatter = mat2.scatter;
}

/**
 * Returns the u,v coordinates of a point on the sphere.
 * @param p: a given point on the sphere of radius one, centered at the origin.
 * @param u: returned value [0,1] of angle around the Y axis from X=-1.
 * @param v: returned value [0,1] of angle from Y=-1 to Y=+1.
 *     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
 *     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
 *     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>
*/
void get_sphere_uv(t_vec3 p, double *u, double *v)
{
	double phi;
	double theta;

	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + M_PI;
	*u = phi / (2 * M_PI);
	*v = theta / M_PI;
}

t_color checker_value(t_hit *rec)
{

	double checker_u = rec->u * rec->texture->inv_scale * 2;
	double checker_v = rec->v * rec->texture->inv_scale;

	int x_integer = floor(checker_u);
	int y_integer = floor(checker_v);

	bool isEven = (x_integer + y_integer) % 2 == 0;

	return isEven ? rec->texture->color_value_1 : rec->texture->color_value_2;
}

bool	scatter_lambertian(t_ray *r_in, t_hit *rec, t_color *attenuation, t_ray *scattered)
{
	(void)*r_in;
	t_vec3 scatter_direction;

	scatter_direction = vec3_plus_vec3(rec->normal, random_unit_vector());
	if (near_zero(scatter_direction))
		scatter_direction = rec->normal;
	*scattered = create_ray(rec->p, scatter_direction);
	if (rec->texture == NULL)
		*attenuation = rec->mat->albedo;
	else 
		*attenuation = checker_value(rec);
	return (true);
}

t_vec3 reflect(const t_vec3 v, const t_vec3 n) {
	return (vec3_minus_vec3(v, vec3_times_d(n, 2 * dot(v, n))));
}

bool	scatter_metal(t_ray *r_in, t_hit *rec, t_color *attenuation, t_ray *scattered)
{
	t_vec3 reflected;

	reflected = reflect(unit_vector(r_in->direction), rec->normal);
	*scattered = create_ray(rec->p, vec3_plus_vec3(reflected, vec3_times_d(random_unit_vector(), rec->mat->fuzz)));
	if (rec->texture == NULL)
		*attenuation = rec->mat->albedo;
	else 
		*attenuation = checker_value(rec);
	return (dot(scattered->direction, rec->normal) > 0);
}
