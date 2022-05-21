#include "../include/object.h"

double	object_solve_ray_equation(t_object *const me, t_ray ray)
{
	return ((*me->vptr->solve_ray_equation)(me, ray));
}

t_vector	object_calc_normal(t_object *me, t_vector cross_point)
{
	return ((*me->vptr->calc_normal)(me, cross_point));
}

t_vector	object_calc_bumpmap_normal(t_object *me, t_vector cross_point)
{
	return ((*me->vptr->calc_bumpmap_normal)(me, cross_point));
}

t_color	object_calc_color(t_object *me, t_vector cross_point)
{
	return ((*me->vptr->calc_color)(me, cross_point));
}
