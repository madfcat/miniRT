#include "miniRT.h"

int	ft_error(void)
{
	return (1);
}
// TODO: calculate focal_length from FOV angle

void	init_camera(t_camera *c,
			double focal_length, double viewport_height)
{
	double	viewport_width;
	t_vec3	viewport_upper_left;

	// focal_length = 1.0;
	// viewport_height = 2.0;
	viewport_width = viewport_height * (WWIDTH * 1.0) / (WHEIGHT * 1.0);
	c->camera_center = init_vec3(0, 0, 0);
	c->viewport_u = init_vec3(viewport_width, 0, 0);
	c->viewport_v = init_vec3(0, viewport_height * -1.0, 0);
	c->pixel_delta_u = vec3_div_d(c->viewport_u, WWIDTH * 1.0);
	c->pixel_delta_v = vec3_div_d(c->viewport_v, WHEIGHT * 1.0);
	viewport_upper_left = vec3_minus_vec3(c->camera_center,
			init_vec3(0, 0, focal_length));
	viewport_upper_left = vec3_minus_vec3(viewport_upper_left,
			vec3_times_d(c->viewport_v, 0.5));
	viewport_upper_left = vec3_minus_vec3(viewport_upper_left,
			vec3_times_d(c->viewport_u, 0.5));
	c->pixel00_loc = vec3_plus_vec3(viewport_upper_left,
			vec3_times_d(vec3_plus_vec3(c->pixel_delta_v,
					c->pixel_delta_u), 0.5));
}

/**
 * Returns a random point in the square surrounding a pixel at the origin
*/
t_vec3	pixel_sample_square(t_camera *c)
{
	double	px;
	double	py;

	px = -0.5 + random_double();
	py = -0.5 + random_double();
	return (vec3_plus_vec3(vec3_times_d(c->pixel_delta_u, px), vec3_times_d(c->pixel_delta_v, py)));

}
/**
 * Get a randomly sampled camera ray for the pixel at location j, i.
*/
t_ray	get_ray(int j, int i, t_camera *c)
{
	t_vec3		pixel_center;
	t_vec3		pixel_sample;
	t_ray		r;

	pixel_center = vec3_plus_vec3(c->pixel00_loc, vec3_plus_vec3(vec3_times_d(c->pixel_delta_u, j * 1.0), vec3_times_d(c->pixel_delta_v, i * 1.0)));
	pixel_sample = vec3_plus_vec3(pixel_center, pixel_sample_square(c));

	r.origin = c->camera_center;
	r.direction = vec3_minus_vec3(pixel_sample, r.origin);

	return (r);
}

void	make_image(t_master *m, mlx_image_t *img)
{
	t_camera	c;
	t_ray		r;
	int			i;
	int			j;
	int   		sample;
	int    		samples_per_pixel = 100;
	t_color 	pixel_color;


	init_camera(&c, 1.0, 2.0);
	i = 0;
	j = 0;
	while (i < WHEIGHT)
	{
		while (j < WWIDTH)
		{
			pixel_color = init_vec3(0, 0, 0);
			sample = 0;
			while (sample < samples_per_pixel)
			{
				r = get_ray(j, i, &c);
				pixel_color = vec3_plus_vec3(pixel_color, ray_color(m, &r));
				sample++;
			}

			mlx_put_pixel(img, j, i, color_to_rgba(pixel_color, samples_per_pixel));
			j++;
		}
		i++;
		j = 0;
	}
	return ;
}

int	render(t_master *m)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WWIDTH, WHEIGHT, "miniRT", true);
	if (!mlx)
		return (ft_error());
	img = mlx_new_image(mlx, WWIDTH, WHEIGHT);
	if (!img)
		return (ft_error());
	make_image(m, img);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (ft_error());
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
/**
 * Initializes sphere_vector in the master struct
*/
void	init_spheres(t_master *m, int size)
{
	// m->spheres = (t_sphere *)malloc(size * sizeof(t_sphere));
	(m->sphere_vector).data = (t_sphere *)malloc(size * sizeof(t_sphere));
	// m->spheres = (&(m->sphere_vector))->data;
	(&(m->sphere_vector))->size = 0;
	(&(m->sphere_vector))->element_size = sizeof(t_sphere);
}

int	main(void)
{
	t_master	m;
	t_sphere	first_sphere;
	t_sphere	second_sphere;

	first_sphere.center = init_vec3(0, 0, -1.0);
	first_sphere.radius = 0.5;
	init_spheres(&m, 20);
	push_back(&(m.sphere_vector), &first_sphere);
	// ((t_sphere *)m.sphere_vector.data)[m.sphere_vector.size++] = first_sphere;

	second_sphere.center = init_vec3(0, -100.5, -1);
	second_sphere.radius = 100;
	push_back(&(m.sphere_vector), &second_sphere);

	render(&m);
	return (0);
}
