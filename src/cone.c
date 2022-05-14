#include "../include/object.h"

static double	cone_solve_ray_equation(t_object *me, t_ray ray);
static t_vector	cone_calc_normal(t_object *me, t_vector cross_point);

void	cone_ctor(
			t_cone *me,
			t_vector center,
			t_vector normal,
			double aperture,
			t_color diffuse_reflection_coefficient,
			t_color specular_reflection_coefficient)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &cone_solve_ray_equation,
			.calc_radiance = &calc_radiance_,
			.calc_normal = &cone_calc_normal
	};

	object_ctor(&me->super, center, diffuse_reflection_coefficient, specular_reflection_coefficient);
	me->super.vptr = &vtbl;
	me->normal = normal;
	me->aperture = aperture;
}

double	cone_solve_ray_equation(t_object *const me_, t_ray ray)
{
	// TODO: solve ray equation
}

static t_vector	cone_calc_normal(t_object *const me, t_vector cross_point)
{
	// TODO: calc normal
}
