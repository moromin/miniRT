#include "../include/scene.h"

char	*load_sphere(t_program *p, char **info)
{
	t_slice		*sp;
	t_vector	center;
	double		radius;
	t_color		col;

	sp = make(sizeof(t_sphere), 1, 1);
	if (!get_vector_from_str(info[0], &center))
		return (ERR_MISCONFIGURED_SPHERE);
	if (!ft_strtod(info[1], &radius))
		return (ERR_MISCONFIGURED_SPHERE);
	if (!get_color_from_str(info[2], &col) && check_color_range(col, 0.0, 255.0))
		return (ERR_MISCONFIGURED_SPHERE);
	sphere_ctor(get(sp, 0), radius, center, col, color(0, 0, 0));
	append(p->objects, &sp);
	return (NO_ERR);
}

char	*load_plane(t_program *p, char **info)
{
	t_slice		*pl;
	t_vector	center;
	t_vector	normal;
	t_color		col;

	pl = make(sizeof(t_plane), 1, 1);
	if (!get_vector_from_str(info[0], &center))
		return (ERR_MISCONFIGURED_PLANE);
	if (!get_vector_from_str(info[1], &normal)
			&& check_vector_range(normal, -1.0, 1.0))
		return (ERR_MISCONFIGURED_PLANE);
	if (!get_color_from_str(info[2], &col) && check_color_range(col, 0.0, 255.0))
		return (ERR_MISCONFIGURED_PLANE);
	plane_ctor(get(pl, 0), center, normal, col, color(0, 0, 0));
	append(p->objects, &pl);
	return (NO_ERR);
}
