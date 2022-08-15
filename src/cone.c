#include "../include/object.h"
#include "../include/private_object_method.h"

void	cone_ctor(t_cone *me, t_cone_attrs *attrs)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &cone_solve_ray_equation,
			.calc_normal = &cone_calc_normal,
			.calc_bumpmap_normal = &cone_calc_bumpmap_normal,
			.calc_color = &cone_calc_color,
	};
	const t_vector			e1 = ({
		const t_vector	ex = vec_init(1, 0, 0);
		t_vector	vec;
		if (vec_dot(attrs->normal, ex) == 1)
			vec = ex;
		else
			vec = vec_cross(attrs->normal, ex);
		vec;
	});

	object_ctor(&me->super, attrs->center, attrs->k_diffuse, attrs->k_specular);
	me->super.vptr = &vtbl;
	me->normal = attrs->normal;
	me->aperture = attrs->aperture;
	me->e1 = e1;
	me->e2 = vec_cross(e1, me->normal);
}
