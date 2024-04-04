#include "miniRT.h"

void	set_face_normal(const t_ray *r, const t_vec3 outward_normal, t_hit *rec)
{
	rec->front_face = dot(r->direction, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec3_minus_vec3(create_vec3(0, 0, 0), outward_normal);
}

bool	hit_sphere(t_sphere sphere, t_ray *r, t_interval ray_t, t_hit *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	root;

	t_vec3 oc = vec3_minus_vec3(r->origin, sphere.center);
	a = vec3length_squared(r->direction);
	half_b = dot(oc, r->direction);
	c = vec3length_squared(oc) - sphere.radius * sphere.radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);

	root = (-half_b - sqrt(discriminant)) / a;
	if (!interval_surrounds(root, ray_t))
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (!interval_surrounds(root, ray_t))
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	t_vec3 outward_normal = vec3_div_d(vec3_minus_vec3(rec->p, sphere.center), sphere.radius);
	set_face_normal(r, outward_normal, rec);
	get_sphere_uv(outward_normal, &rec->u, &rec->v);
	rec->mat = sphere.mat;
	rec->texture = sphere.texture;
	return (true);
}

bool	hit_plane(t_plane plane, t_ray *r, t_interval ray_t, t_hit *rec)
{
	double	denominator;
	double	numerator;
	double	t;

 	// Calculate the denominator of the ray-plane intersection equation
	denominator = dot(plane.normal, r->direction);
	// Check if the ray is parallel or nearly parallel to the plane
	if (fabs(denominator) < 0.0001)
		return (false);
	// Calculate the numerator of the ray-plane intersection equation
	numerator = dot(vec3_minus_vec3(plane.point, r->origin), plane.normal);
	 // Calculate the parameter 't' representing the intersection point along the ray
	t = numerator / denominator;
	// Check if the intersection point 't' is within the valid interval of the ray
	if (!interval_surrounds(t, ray_t))
		return (false);

	rec->t = t;
	// Calculate the intersection point 'p' using the ray equation
	rec->p = ray_at(r, rec->t);
	// Set the normal direction based on the ray direction and the plane normal
	set_face_normal(r, plane.normal, rec); 
	rec->mat = plane.mat;
	rec->texture = plane.texture;
	return (true);
}

// TODO: redo for the objects.
// Now works for spheres
bool	hit(t_ray *r, t_interval ray_t, t_hit *rec, t_master *m)
{
	t_hit	temp_rec;
	bool	hit_anything;
	double	closest_so_far;
	int		i;

	hit_anything = false;
	closest_so_far = ray_t.max;
	i = 0;
	while (i < m->sphere_vector.size)
	{

		if (hit_sphere(((t_sphere *)(m->sphere_vector.data))[i], r, create_interval(ray_t.min, closest_so_far), &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	i = 0;
	while (i < m->plane_vector.size)
	{
		if (hit_plane(((t_plane *)(m->plane_vector.data))[i], r, create_interval(ray_t.min, closest_so_far), &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}
