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

	return (true);
}

// TODO: redo for the objects.
// Now works for spheres
bool	hit(t_ray *r, t_interval ray_t, t_hit *rec, t_vector spheres_vector)
{
	t_hit	temp_rec;
	bool	hit_anything;
	double	closest_so_far;
	int		i;

	hit_anything = false;
	closest_so_far = ray_t.max;
	i = 0;
	while (i < spheres_vector.size)
	{

		if (hit_sphere(((t_sphere *)(spheres_vector.data))[i], r, create_interval(ray_t.min, closest_so_far), &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}
