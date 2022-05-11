#include "../include/scene.h"

void	load_ambient(t_program *program, char **info, char **err)
{
	double		ratio;
	t_color		c;

	if (!(ft_strtod(info[0], &ratio) && 0.0 <= ratio && ratio <= 1.0))
		*err = ERR_MISCONFIGURED_AMBIENT;
	if (get_color_from_str(info[1], &c))
		program->ambient = ambient(color_mult(c, ratio));
	else
		*err = ERR_MISCONFIGURED_AMBIENT;
}

void	load_camera(t_program *program, char **info, char **err)
{
	double		fov;

	if (!get_vector_from_str(info[0], &program->camera.pos))
		*err = ERR_MISCONFIGURED_CAMERA;
	if (!(get_vector_from_str(info[1], &program->camera.normal)
		&& check_vector_range(program->camera.normal, -1.0, 1.0)))
		*err = ERR_MISCONFIGURED_CAMERA;
	if (ft_strtod(info[2], &fov) && 0.0 <= fov && fov <= 180.0)
		program->camera.fov = fov;
	else
		*err = ERR_MISCONFIGURED_CAMERA;
}
