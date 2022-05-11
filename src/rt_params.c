#include "../include/scene.h"

char	*load_ambient(t_program *p, char **info)
{
	double		ratio;
	t_color		c;

	if (!(ft_strtod(info[0], &ratio) && 0.0 <= ratio && ratio <= 1.0))
		return (ERR_MISCONFIGURED_AMBIENT);
	if (get_color_from_str(info[1], &c))
		p->ambient = ambient(color_mult(c, ratio));
	else
		return (ERR_MISCONFIGURED_AMBIENT);
	return (NO_ERR);
}

char	*load_camera(t_program *p, char **info)
{
	double		fov;

	if (!get_vector_from_str(info[0], &p->camera.pos))
		return (ERR_MISCONFIGURED_CAMERA);
	if (!(get_vector_from_str(info[1], &p->camera.normal)
			&& check_vector_range(p->camera.normal, -1.0, 1.0)))
		return (ERR_MISCONFIGURED_CAMERA);
	if (ft_strtod(info[2], &fov) && 0.0 <= fov && fov <= 180.0)
		p->camera.fov = fov;
	else
		return (ERR_MISCONFIGURED_CAMERA);
	return (NO_ERR);
}

char	*load_light(t_program *p, char **info)
{
	t_light	l;
	double	ratio;
	t_color	c;

	if (!get_vector_from_str(info[0], &l.coordinate))
		return (ERR_MISCONFIGURED_LIGHT);
	if (!(ft_strtod(info[1], &ratio) && 0.0 <= ratio && ratio <= 1.0))
		return (ERR_MISCONFIGURED_AMBIENT);
	if (get_color_from_str(info[2], &c))
		l.intensity = color_mult(c, ratio);
	else
		return (ERR_MISCONFIGURED_AMBIENT);
	append(p->lights, &l);
	return (NO_ERR);
}
