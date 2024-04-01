#include "vec3.h"

double dot(const t_vec3 u, const t_vec3 v)
{
	return(u.x * v.x + u.y * v.y + u.z * v.z);
}
