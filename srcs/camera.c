#include "miniRT.h"

void	setup_camera(t_camera *c)
{
	c->lookfrom = create_vec3(-2, 2, 1);
	c->lookat = create_vec3(0, 0, -1);
	c->vup = create_vec3(0, 1, 0);
	c->samples_per_pixel = 20; // 100 for better resolution, slower rendering
	c->max_depth = 50;
	c->vfov = 20;
}

void	init_camera(t_camera *c)
{
	double	viewport_width;
	t_vec3	viewport_upper_left;

	setup_camera(c);
	c->camera_center = c->lookfrom;

	// Determine viewport dimensions
	double focal_length = vec3length(vec3_minus_vec3(c->lookfrom, c->lookat));
	double theta = degrees_to_radians(c->vfov);
	double h = tan(theta / 2);
	double viewport_height = 2 * h * focal_length;
	viewport_width = viewport_height * (WWIDTH * 1.0) / (WHEIGHT * 1.0);

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	c->w = unit_vector(vec3_minus_vec3(c->lookfrom, c->lookat));
	c->u = unit_vector(cross(c->vup, c->w));
	c->v = cross(c->w, c->u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	c->viewport_u = vec3_times_d(c->u, viewport_width);
	c->viewport_v = vec3_times_d(c->v, viewport_height * (-1));

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	c->pixel_delta_u = vec3_div_d(c->viewport_u, WWIDTH * 1.0);
	c->pixel_delta_v = vec3_div_d(c->viewport_v, WHEIGHT * 1.0);

	// Calculate the location of the upper left pixel.
	viewport_upper_left = vec3_minus_vec3(c->camera_center,
			vec3_times_d(c->viewport_u, 0.5));
	viewport_upper_left = vec3_minus_vec3(viewport_upper_left,
			vec3_times_d(c->viewport_v, 0.5));
	viewport_upper_left = vec3_minus_vec3(viewport_upper_left,
			vec3_times_d(c->w, focal_length));
	c->pixel00_loc = vec3_plus_vec3(viewport_upper_left,
			vec3_times_d(vec3_plus_vec3(c->pixel_delta_v,
					c->pixel_delta_u), 0.5));
}
