#include "miniRT.h"

t_material create_material(t_color albedo, double fuzz, Scatter scatter)
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

bool	scatter_lambertian(t_ray *r_in, t_hit *rec, t_color *attenuation, t_ray *scattered)
{
	(void)*r_in;
	t_vec3 scatter_direction;

	scatter_direction = vec3_plus_vec3(rec->normal, random_unit_vector());
	if (near_zero(scatter_direction))
		scatter_direction = rec->normal;
	*scattered = create_ray(rec->p, scatter_direction);
	*attenuation = rec->mat->albedo;
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
	*attenuation = rec->mat->albedo;
	return (dot(scattered->direction, rec->normal) > 0);
}
