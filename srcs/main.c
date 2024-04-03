#include "miniRT.h"

int	ft_error(void)
{
	return (1);
}

/**
 * Initializes sphere_vector in the master struct
*/
void	init_spheres(t_master *m, int size)
{
	(m->sphere_vector).data = (t_sphere *)malloc(size * sizeof(t_sphere));
	(&(m->sphere_vector))->size = 0;
	(&(m->sphere_vector))->element_size = sizeof(t_sphere);
}

t_sphere	create_sphere(t_vec3 center, double radius, t_material mat)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	sphere.mat = (t_material *)malloc(sizeof(t_material));
	if (sphere.mat == NULL)
	{
		perror("Memory allocation failed\n");
		exit(1);
	}
	init_material(sphere.mat, mat);
	return (sphere);
}
/**
 * Destroys sphere by freeing the material
*/
void	destroy_sphere(t_sphere *sphere)
{
	free(sphere->mat);
}

int	main(void)
{
	t_master	m;
	t_sphere	ground_sphere;
	t_material	ground_material;
	t_sphere	center_sphere;
	t_material	center_material;
	t_sphere	left_sphere;
	t_material	left_material;
	t_sphere	right_sphere;
	t_material	right_material;

	init_spheres(&m, 20);

	ground_material = create_material(create_vec3(0.8, 0.8, 0.0),
			0.0,
			&scatter_lambertian);
	ground_sphere = create_sphere(create_vec3(0.0, -100.5, -1.0),
			100,
			ground_material);
	push_back(&(m.sphere_vector), &ground_sphere);

	center_material = create_material(create_vec3(0.7, 0.3, 0.3),
			0.0,
			&scatter_lambertian);
	center_sphere = create_sphere(create_vec3(0.0, 0.0, -1.0),
			0.5,
			center_material);
	push_back(&(m.sphere_vector), &center_sphere);

	left_material = create_material(create_vec3(0.8, 0.8, 0.8),
			0.3,
			&scatter_metal);
	left_sphere = create_sphere(create_vec3(-1.0, 0.0, -1.0),
			0.5,
			left_material);
	push_back(&(m.sphere_vector), &left_sphere);

	right_material = create_material(create_vec3(0.8, 0.6, 0.2),
			0.5,
			&scatter_metal);
	right_sphere = create_sphere(create_vec3(1.0, 0.0, -1.0),
			0.5,
			right_material);
	push_back(&(m.sphere_vector), &right_sphere);

	render(&m);

	destroy_sphere(&ground_sphere);
	destroy_sphere(&center_sphere);
	destroy_sphere(&left_sphere);
	destroy_sphere(&right_sphere);

	return (0);
}
