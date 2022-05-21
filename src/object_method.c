#include "../include/object.h"

double	solve_ray_equation(t_object *const me, t_ray ray)
{
	return ((*me->vptr->solve_ray_equation)(me, ray));
}

t_vector	calc_normal(t_object *me, t_vector cross_point)
{
	return ((*me->vptr->calc_normal)(me, cross_point));
}

t_vector	calc_bumpmap_normal(t_object *me, t_vector cross_point)
{
	return ((*me->vptr->calc_bumpmap_normal)(me, cross_point));
}

t_color	calc_color(t_object *me, t_vector cross_point)
{
	return ((*me->vptr->calc_color)(me, cross_point));
}
