#include "../include/color.h"
#include "../include/material.h"
#include "../include/object.h"
#include "../include/private_object_method.h"

void	sphere_ctor(t_sphere *const me, double radius, t_vector center,
			t_color k_diffuse, t_color k_specular)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &sphere_solve_ray_equation,
			.calc_normal = &sphere_calc_normal,
			.calc_bumpmap_normal = &sphere_calc_bumpmap_normal,
			.calc_color = &sphere_calc_color
	};

	object_ctor(&me->super, center, k_diffuse, k_specular);
	me->super.vptr = &vtbl;
	me->radius = radius;
}
