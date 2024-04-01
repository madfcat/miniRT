#include "miniRT.h"

t_point3	ray_at(t_ray r, double t)
{
	return (vec3_plus_vec3(r.origin, vec3_times_d(r.direction, t)));
}

t_ray	init_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ret;

	ret.origin = origin;
	ret.direction = direction;
	return (ret);
}

unsigned int	color_to_rgba(t_color c)
{
	return (lround(c.x * 255) << 24 | lround(c.y * 255) << 16
		| lround(c.z * 255) << 8 | 255);
}

// double hit_sphere(const t_vec3 center, double radius, const t_ray r)
// {
// 	double	a;
// 	double	half_b;
// 	double	c;
// 	double	discriminant;

// 	t_vec3 oc = vec3_minus_vec3(r.origin, center);
// 	a = vec3length_squared(r.direction);
// 	half_b = dot(oc, r.direction);
// 	c = vec3length_squared(oc) - radius * radius;
// 	discriminant = half_b * half_b - a * c;
// 	if (discriminant < 0)
// 		return (-1.0);
// 	return ((-half_b - sqrt(discriminant)) / a);
// }

t_color	ray_color(t_master *m, t_ray r)
{
	t_vec3	unit_direction;
	double	a;
	t_color	ret;
	// double t;
	// t_vec3 n;
	t_hit	rec;

	if (hit(r, 0.0, INFINITY, &rec, m->sphere_vector))
	{
		return (vec3_plus_vec3(rec.normal, init_vec3(1, 1, 1)));
	}


/* 	t_sphere sphere = ((t_sphere *)m->sphere_vector.data)[0];

	(void)m;
	t_hit rec;

	// t = hit_sphere(m->spheres[0], r, 0.0, INFINITY, &rec);
	t = hit_sphere(sphere, r, 0.0, INFINITY, &rec);
	// t = hit_sphere(m->spheres[0], 0.5, r, &rec);

	if (t > 0.0)
	{
		n = unit_vector(vec3_minus_vec3(ray_at(r, t), sphere.center));
		return vec3_times_d(init_vec3(n.x + 1, n.y + 1, n.z + 1), 0.33);
	} */
	unit_direction = unit_vector(r.direction);
	a = 0.5 * (unit_direction.y + 1.0);
	ret = vec3_plus_vec3(vec3_times_d(init_vec3(1.0, 1.0, 1.0), 1.0 - a),
			vec3_times_d(init_vec3(0.5, 0.7, 1.0), a));
	return (ret);
}
