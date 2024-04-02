#include "miniRT.h"

double dot(const t_vec3 u, const t_vec3 v)
{
	return(u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3 random_vec3()
{
	return (init_vec3(random_double(), random_double(), random_double()));
}

t_vec3 random_vec3_range(double min, double max)
{
	return (init_vec3(random_double(min, max), random_double(min, max), random_double(min, max)));
}
