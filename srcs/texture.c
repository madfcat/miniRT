#include "miniRT.h"

t_texture	create_texture(t_texture_type type, t_color color_value_1,
		t_color color_value_2, double inv_scale)
{
	t_texture	texture;

	texture.type = type;
	texture.color_value_1 = color_value_1;
	texture.color_value_2 = color_value_2;
	texture.inv_scale = inv_scale;
	return (texture);
}
