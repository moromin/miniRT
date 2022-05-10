#include "../include/scene.h"

void	load_ambient(t_program *program, char **info)
{
	double		ratio;
	char		**params;
	t_vector	rgb;

	// TODO: free something
	if (!(ft_strtod(info[0], &ratio) && 0.0 <= ratio && ratio <= 1.0))
		exit_with_error_message(ERR_MISCONFIGURED_AMBIENT);
	params = x_split(info[1], ',');
	if (count_2d_array((void ***)&params) != 3)
		exit_with_error_message(ERR_MISCONFIGURED_AMBIENT);
	if (!(get_rgb_from_str(params, &rgb)))
		exit_with_error_message(ERR_MISCONFIGURED_AMBIENT);
	rgb = vec_mult(rgb, ratio);
	program->ambient = rgb_to_int(rgb.x, rgb.y, rgb.z);
}
