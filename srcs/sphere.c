#include "miniRT.h"

/**
 * Initializes sphere_vector in the master struct
*/
void	init_spheres(t_master *m, int size)
{
	(m->sphere_vector).data = (t_sphere *)malloc(size * sizeof(t_sphere));
	(&(m->sphere_vector))->size = 0;
	(&(m->sphere_vector))->element_size = sizeof(t_sphere);
}

t_sphere	create_sphere(t_vec3 center, double radius, t_material *mat, t_texture *texture)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	// sphere.mat = (t_material *)malloc(sizeof(t_material));
	// if (sphere.mat == NULL)
	// {
	// 	perror("Memory allocation failed\n");
	// 	exit(1);
	// }
	// init_material(sphere.mat, mat);
	sphere.mat = mat;
	sphere.texture = texture;
	return (sphere);
}
// /**
//  * Destroys sphere by freeing the material
// */
// void	destroy_sphere(t_sphere *sphere)
// {
// 	free(sphere->mat);
// }
