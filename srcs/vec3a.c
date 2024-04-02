#include "miniRT.h"

t_vec3	vec3_plus_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x + v.x;
	ret.y = u.y + v.y;
	ret.z = u.z + v.z;
	return (ret);
}

t_vec3	vec3_minus_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x - v.x;
	ret.y = u.y - v.y;
	ret.z = u.z - v.z;
	return (ret);
}

t_vec3	vec3_times_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.x * v.x;
	ret.y = u.y * v.y;
	ret.z = u.z * v.z;
	return (ret);
}

t_vec3	vec3_times_d(t_vec3 u, double t)
{
	t_vec3	ret;

	ret.x = u.x * t;
	ret.y = u.y * t;
	ret.z = u.z * t;
	return (ret);
}

t_vec3	cross(t_vec3 u, t_vec3 v)
{
	t_vec3	ret;

	ret.x = u.y * v.z - u.z * v.y;
	ret.y = u.z * v.x - u.x * v.z;
	ret.z = u.x * v.y - u.y * v.x;
	return (ret);
}
