#include "miniRT.h"

int	ft_error(void)
{
	return (1);
}

int	main(void)
{
	t_master	m;
	// t_sphere	ground_sphere;
	t_material	ground_material;
	t_sphere	center_sphere;
	t_material	center_material;
	t_texture	center_texture;
	t_sphere	left_sphere;
	t_material	left_material;
	t_sphere	right_sphere;
	t_material	right_material;

	t_plane		first_plane;

	init_spheres(&m, 20);

	ground_material = create_material(create_vec3(0.8, 0.8, 0.0),
			0.0,
			&scatter_lambertian);
	// ground_sphere = create_sphere(create_vec3(0.0, -100.5, -1.0),
	// 		100,
	// 		&ground_material,
	// 		NULL);
	// push_back(&(m.sphere_vector), &ground_sphere);

	center_texture = create_texture(CHECKERED, create_vec3(0.9, 0.3, 0.1), create_vec3(0.9, 0.1, 0.0), 20);
	center_material = create_material(create_vec3(0.7, 0.3, 0.3),
			0.0,
			&scatter_lambertian);
	center_sphere = create_sphere(create_vec3(0.0, 0.0, -1.0),
			0.5,
			&center_material,
			NULL);
	push_back(&(m.sphere_vector), &center_sphere);

	left_material = create_material(create_vec3(0.8, 0.8, 0.8),
			0.1,
			&scatter_metal);
	left_sphere = create_sphere(create_vec3(-1.0, 0.0, -1.0),
			0.5,
			&left_material,
			&center_texture);
	push_back(&(m.sphere_vector), &left_sphere);

	right_material = create_material(create_vec3(0.8, 0.6, 0.2),
			0.5,
			&scatter_metal);
	right_sphere = create_sphere(create_vec3(1.0, 0.0, -1.0),
			0.5,
			&right_material,
			NULL);
	push_back(&(m.sphere_vector), &right_sphere);

	init_planes(&m, 2);

	first_plane = create_plane(create_vec3(0, -1, 0), create_vec3(0, 1, 0), &ground_material, NULL);
	push_back(&(m.plane_vector), &first_plane);

	render(&m);
	free(m.sphere_vector.data);
	// destroy_sphere(&ground_sphere);
	// destroy_sphere(&center_sphere);
	// destroy_sphere(&left_sphere);
	// destroy_sphere(&right_sphere);
	return (0);
}
