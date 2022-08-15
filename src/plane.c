#include "../include/object.h"
#include "../include/private_object_method.h"

void	plane_ctor(
		t_plane *const me,
		t_vector center,
		t_vector normal,
		t_color k_diffuse,
		t_color k_specular)
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

	object_ctor(&me->super, center, k_diffuse, k_specular);
	me->super.vptr = &vtbl;
	me->normal = normal;
	me->eu = eu;
	me->ev = vec_cross(me->normal, eu);
}
