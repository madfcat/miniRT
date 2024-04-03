#include "miniRT.h"

double	dot(const t_vec3 u, const t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	random_vec3(void)
{
	return (create_vec3(random_double(), random_double(), random_double()));
}

t_vec3	random_vec3_range(double min, double max)
{
	return (create_vec3(random_double(min, max),
			random_double(min, max), random_double(min, max)));
}

/**
 * Returns true if the vector is close to zero in all dimensions.
*/
bool	near_zero(t_vec3 v)
{
	double s;

	s = 1e-8;
	return (fabs(v.x) < s && fabs(v.y) < s && fabs(v.z) < s);
}
