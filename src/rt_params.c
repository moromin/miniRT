#include "../include/scene.h"

void	load_ambient(t_program *program, char **info)
{
	double		ratio;
	char		**params;
	t_color		c;

	// TODO: free grogram
	if (!(ft_strtod(info[0], &ratio) && 0.0 <= ratio && ratio <= 1.0))
		exit_with_error_message(ERR_MISCONFIGURED_AMBIENT);
	params = x_split(info[1], ',');
	if (count_2d_array((void **)params) != 3)
		exit_with_error_message(ERR_MISCONFIGURED_AMBIENT);
	if (!(get_color_from_strs(params, &c)))
		exit_with_error_message(ERR_MISCONFIGURED_AMBIENT);
	program->ambient = ambient(color_mult(c, ratio));
	free_2d_array((void **)params);
}
