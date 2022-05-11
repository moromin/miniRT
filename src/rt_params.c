#include "../include/scene.h"

void	load_ambient(t_program *program, char **info, char **err)
{
	double		ratio;
	char		**params;
	t_color		c;

	if (!(ft_strtod(info[0], &ratio) && 0.0 <= ratio && ratio <= 1.0))
		*err = ERR_MISCONFIGURED_AMBIENT;
	params = x_split(info[1], ',');
	if (!(count_2d_array((void **)params) == 3 && get_color_from_strs(params, &c)))
		*err = ERR_MISCONFIGURED_AMBIENT;
	else
		program->ambient = ambient(color_mult(c, ratio));
	free_2d_array((void **)params);
}
