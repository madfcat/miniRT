#include "miniRT.h"

t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	while (true)
	{
		p = random_vec3_range(-1, 1);
		if (vec3length_squared(p) < 1)
			return (p);
	}
}

t_vec3	random_unit_vector(void)
{
	return (unit_vector(random_in_unit_sphere()));
}

t_vec3	random_on_hemisphere(t_vec3 *normal)
{
	t_vec3	on_unit_sphere;

	on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, *normal) > 0.0) // In the same hemisphere as the normal
		return (on_unit_sphere);
	return (vec3_times_d(on_unit_sphere, -1));
}
