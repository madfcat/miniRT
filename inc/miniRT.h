#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h> // change this to libft to use memcpy
// TODO: remove this header
# include <stdio.h>
# define WWIDTH 1280
# define WHEIGHT 720


/* Utilities */

double	degrees_to_radians(double degrees);
double	random_double();

/* Interval */

typedef struct s_interval
{
	double	min;
	double	max;
}	t_interval;

t_interval	create_interval( double min, double max);
bool		interval_surrounds(double x, t_interval interval);
double		clamp(double x, t_interval interval);

/* Vector Array */

typedef struct s_vector
{
	void	*data;		// Pointer to dynamically allocated array
	int		size;		// Number of elements currently in the vector
	int		capacity;	// Number of elements the vector can store
	int		element_size; // Size of each element in bytes
}	t_vector;

void push_back(t_vector *vec, void *value);
void init_vector(t_vector *vec, int initial_size, int element_size);

/* Vec3 */

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_color;
typedef t_vec3	t_point3;

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
t_vec3	create_vec3(double x, double y, double z);
t_vec3	random_vec3(void);
t_vec3	random_vec3_range(double min, double max);
t_vec3	random_unit_vector(void);
bool	near_zero(t_vec3 v);

/* Materials */
typedef struct s_ray t_ray;
typedef struct s_hit t_hit;
typedef bool (*Scatter)(t_ray *, t_hit *, t_color *, t_ray *);

typedef struct	s_material
{
	t_color		albedo;
	double		fuzz;
	Scatter		scatter;
}	t_material;


typedef struct	s_lambertian
{
	t_color	albedo;
}	t_lambertian;

typedef struct	s_metal
{
	t_color	albedo;
}	t_metal;

typedef struct s_ray t_ray;
typedef struct s_hit t_hit;

t_material	create_material(t_color albedo, double fuzz, Scatter scatter);
void		init_material(t_material *mat, t_material mat2);
bool		scatter_lambertian(t_ray *r_in, t_hit *rec, t_color *attenuation, t_ray *scattered);
bool		scatter_metal(t_ray *r_in, t_hit *rec, t_color *attenuation, t_ray *scattered);

/* Objects */

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
	t_point3	pixel00_loc;
	int			samples_per_pixel;
	int			max_depth;
	double		vfov;
	t_point3	lookfrom;
	t_point3	lookat;
	t_vec3		vup;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
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
	t_material	*mat;
}	t_hit;


/* Sphere */

typedef struct s_sphere
{
	unsigned int	object_index;
	t_point3		center;
	double			radius;
	t_color			color;
	t_material		*mat;
}	t_sphere;

t_vec3	random_on_hemisphere(t_vec3 *normal);

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

/* Ray */

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
} t_ray;

t_ray			create_ray(t_vec3 origin, t_vec3 direction);
unsigned int	color_to_rgba(t_color c, int samples_per_pixel);
t_color			ray_color(t_master *m, t_ray *r, int depth);
t_vec3			ray_at(t_ray *r, double t);

bool hit(t_ray *r, t_interval ray_t, t_hit *rec, t_vector spheres_vector);


#endif
