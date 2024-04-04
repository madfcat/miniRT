#include "miniRT.h"

/**
 * Initializes sphere_vector in the master struct
*/
void	init_planes(t_master *m, int size)
{
	(m->plane_vector).data = (t_plane *)malloc(size * sizeof(t_plane));
	(&(m->plane_vector))->size = 0;
	(&(m->plane_vector))->element_size = sizeof(t_plane);
}

t_plane	create_plane(t_point3 point, t_vec3 normal, t_material *mat, t_texture *texture)
{
	t_plane	plane;

	plane.point = point;
	plane.normal = normal;
	plane.mat = mat;
	plane.texture = texture;
	return (plane);
}
