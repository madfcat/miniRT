#include "miniRT.h"

t_point3	ray_at(t_ray *r, double t)
{
	return (vec3_plus_vec3(r->origin, vec3_times_d(r->direction, t)));
}

t_ray	init_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ret;

	ret.origin = origin;
	ret.direction = direction;
	return (ret);
}

unsigned int	color_to_rgba(t_color c, int samples_per_pixel)
{
	c = vec3_div_d(c, samples_per_pixel);

	t_interval intensity = create_interval(0.000, 0.999);
	return (lround(clamp(c.x, intensity) * 255) << 24 | lround(clamp(c.y, intensity) * 255) << 16
		| lround(clamp(c.z, intensity) * 255) << 8 | 255);
}

t_color	ray_color(t_master *m, t_ray *r, int depth)
{
	t_vec3	unit_direction;
	double	a;
	t_hit	rec;
	t_vec3	direction;
	t_ray	ray;

	if (depth <= 0)
		return (init_vec3(0, 0, 0));
	if (hit(r, create_interval(0.001, INFINITY), &rec, m->sphere_vector))
	{
		// direction = random_on_hemisphere(&rec.normal);
		direction = vec3_plus_vec3(rec.normal, random_unit_vector());
		ray = init_ray(rec.p, direction);
		return (vec3_times_d(ray_color(m, &ray, depth - 1), 0.5));
	}
	unit_direction = unit_vector(r->direction);
	a = 0.5 * (unit_direction.y + 1.0);
	return (vec3_plus_vec3(vec3_times_d(init_vec3(1.0, 1.0, 1.0), 1.0 - a),
			vec3_times_d(init_vec3(0.5, 0.7, 1.0), a)));
}
