#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
} t_ray;

t_vec3	ray_at(t_ray r, double t);
t_ray	init_ray(t_vec3 origin, t_vec3 direction);
unsigned int	color_to_rgba(t_color c);
t_color	ray_color(t_ray r);

#endif
