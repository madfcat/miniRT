#include "miniRT.h"
#include "vec3.h"

int	ft_error(void)
{
	return (1);
}
// TODO: calculate focal_length from FOV angle

void	calculate_camera(t_camera *c,
			double focal_length, double viewport_height)
{
	double	viewport_width;
	t_vec3	viewport_upper_left;

	focal_length = 1.0;
	viewport_height = 2.0;
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

void	make_image(t_master *m, mlx_image_t *img)
{
	t_camera	c;
	t_vec3		pixel_center;
	t_ray		r;
	int			i;
	int			j;

	calculate_camera(&c, 1.0, 2.0);
	i = 0;
	j = 0;
	while (i < WHEIGHT)
	{
		while (j < WWIDTH)
		{
			pixel_center = vec3_plus_vec3(c.pixel00_loc, vec3_plus_vec3(vec3_times_d(c.pixel_delta_u, j * 1.0), vec3_times_d(c.pixel_delta_v, i * 1.0)));
			r.origin = c.camera_center;
			r.direction = vec3_minus_vec3(pixel_center, c.camera_center);
			mlx_put_pixel(img, j, i, color_to_rgba(ray_color(m, r)));
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

	second_sphere.center = init_vec3(0, 0, -1.5);
	second_sphere.radius = 0.5;
	init_spheres(&m, 20);
	push_back(&(m.sphere_vector), &second_sphere);

	render(&m);
	return (0);
}
