#include "../include/object.h"
#include "../include/private_object_method.h"

void	plane_ctor(
		t_plane *const me,
		t_plane_attrs *attrs)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &plane_solve_ray_equation,
			.calc_normal = &plane_calc_normal,
			.calc_bumpmap_normal = &plane_calc_bumpmap_normal,
			.calc_color = &plane_calc_color,
	};
	const t_vector			eu = ({
		const t_vector	ey = vec_init(0, 1, 0);
		t_vector	baseu;

		if (vec_magnitude(vec_cross(me->normal, ey)) == 0)
			baseu = vec_init(1, 0, 0);
		else
			baseu = vec_normalize(vec_cross(me->normal, ey));
		baseu;
	});

	object_ctor(&me->super, attrs->center, attrs->k_diffuse, attrs->k_specular);
	me->super.vptr = &vtbl;
	me->normal = attrs->normal;
	me->eu = eu;
	me->ev = vec_cross(me->normal, eu);
}
