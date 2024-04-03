#include "miniRT.h"

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

void progress_bar(int i)
{
	int times;

	if (i == 0)
	{
		times = WHEIGHT / 100;
		while(times-- >= 0)
			write(1, "#", 1);
		write(1, "\n", 1);
	}
	if (i % 100 == 0)
		write(1, "X", 1);
}

void	make_image(t_master *m, mlx_image_t *img)
{
	t_camera	c;
	t_ray		r;
	int			i;
	int			j;
	int			sample;
	t_color 	pixel_color;

	init_camera(&c);
	i = 0;
	j = 0;
	while (i < WHEIGHT)
	{
		progress_bar(i);
		while (j < WWIDTH)
		{
			pixel_color = create_vec3(0, 0, 0);
			sample = 0;
			while (sample < c.samples_per_pixel)
			{
				r = get_ray(j, i, &c);
				pixel_color = vec3_plus_vec3(pixel_color, ray_color(m, &r, c.max_depth));
				sample++;
			}

			mlx_put_pixel(img, j, i, color_to_rgba(pixel_color, c.samples_per_pixel));
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
