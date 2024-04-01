#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42.h"
# include "vec3.h"
# include <math.h>
# include <stdlib.h>
// TODO: remove this header
# include <stdio.h>
# define WWIDTH 1280
# define WHEIGHT 720

/* Utilities */
# define PI 3.1415926535897932385

/* Vector array */
typedef struct s_sphere t_sphere;

/* typedef struct s_sphere_vector
{
	t_sphere* data;		 // Pointer to dynamically allocated array
	int size;		// Number of elements currently in the vector
	int element_size; // Size of each element in bytes
} t_sphere_vector; */

typedef struct s_vector
{
	void* data;		 // Pointer to dynamically allocated array
	int size;		// Number of elements currently in the vector
	int capacity;	// Number of elements the vector can store
	int element_size; // Size of each element in bytes
} t_vector;

void push_back(t_vector *vec, void *value);
void init_vector(t_vector *vec, int initial_size, int element_size);

/*miniRT*/

typedef struct s_camera
{
	double		focal_length;
	double		viewport_height;
	double		viewport_width;
	t_point3	camera_center;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_vec3		pixel00_loc;
}	t_camera;

typedef struct s_ambient
{
	double	brightness;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_vec3	point;
	t_vec3	orientation;
	t_color	color;
	t_vec3	brightness;
}	t_light;

typedef struct s_hit
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	bool		front_face;
}	t_hit;

typedef struct s_sphere
{
	unsigned int	object_index;
	t_point3		center;
	// t_vec3			origin;
	double			radius;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axisnormal;
	double	radius;
	double	height;
	t_color	color;
}	t_cylinder;

typedef struct s_cone
{
	double	angle;
	double	height;
	t_vec3	tip;
	t_vec3	axis;
}	t_cone;

typedef struct s_master
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		*lights;
	// t_sphere	*spheres;
	t_vector	sphere_vector;
	// t_sphere_vector	sphere_vector;
	t_plane		*planes;
	t_cone		*cones;
	t_cylinder	*cylinders;
}	t_master;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

t_ray			init_ray(t_vec3 origin, t_vec3 direction);
unsigned int	color_to_rgba(t_color c);
t_color			ray_color(t_master *m, t_ray r);
t_vec3			ray_at(t_ray r, double t);

// double			hit_sphere(const t_vec3 center, double radius, const t_ray r);
bool hit_sphere(const t_sphere sphere, const t_ray r, double ray_tmin, double ray_tmax, t_hit *rec);

#endif
