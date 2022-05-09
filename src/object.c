#include <assert.h>

#include "../include/object.h"

static double	solve_ray_equation_(t_object *me, t_ray ray);
static int		raytrace_(t_object *me, t_vector cross_point, t_vector light);

void	object_ctor(t_object *const me, t_vector center)
{
	static t_object_vtbl const	vtbl = {
			&solve_ray_equation_,
			&raytrace_
	};

	me->vptr = &vtbl;
	me->center = center;
}

static double	solve_ray_equation_(t_object *const me, t_ray ray)
{
	(void)me;
	(void)ray;
	assert(0);
}

static int	raytrace_(t_object *me, t_vector cross_point, t_vector light)
{
	(void)me;
	(void)cross_point;
	(void)light;
	assert(0);
}

double	object_solve_ray_equation(t_object *const me, t_ray ray)
{
	return ((*me->vptr->solve_ray_equation)(me, ray));
}

int	object_raytrace(t_object *me, t_vector cross_point, t_vector light)
{
	return ((*me->vptr->raytrace)(me, cross_point, light));
}
