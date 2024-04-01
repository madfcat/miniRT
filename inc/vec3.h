#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3 t_color;
typedef t_vec3 t_point3;

t_vec3	vec3_plus_vec3(t_vec3 u, t_vec3 v);
t_vec3	vec3_minus_vec3(t_vec3 u, t_vec3 v);
t_vec3	vec3_times_vec3(t_vec3 u, t_vec3 v);
t_vec3	vec3_times_d(t_vec3 u, double t);
t_vec3	vec3_div_d(t_vec3 u, double t);
t_vec3	cross(t_vec3 u, t_vec3 v);
t_vec3	unit_vector(t_vec3 v);
double	vec3length(t_vec3 u);
double	vec3length_squared(t_vec3 u);
double	dot(t_vec3 u, t_vec3 v);
t_vec3	init_vec3(double x, double y, double z);

#endif
