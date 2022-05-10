#include <assert.h>

#include "../include/object.h"

static double	object_solve_ray_equation_(t_object *me, t_ray ray);
static t_color	calc_radiance_(t_object *me, t_vector cross_point, t_light light, t_color ambient);
static t_vector	object_calc_normal_(t_object *me, t_vector cross_point);

void	object_ctor(t_object *const me, t_vector center,
			t_color diffuse_reflection_coefficient, t_color specular_reflection_coefficient)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &object_solve_ray_equation_,
			.calc_radiance = &calc_radiance_,
			.calc_normal = &object_calc_normal_
	};

	me->vptr = &vtbl;
	me->center = center;
	me->diffuse_reflection_coefficient = diffuse_reflection_coefficient;
	me->specular_reflection_coefficient = specular_reflection_coefficient;
}

static double	object_solve_ray_equation_(t_object *const me, t_ray ray)
{
	(void)me;
	(void)ray;
	assert(0);
}

/*
 * radiance_ambient: 環境光の反射光の放射輝度
 * radiance_specular: 直接光の鏡面反射光の放射輝度
 * radiance_diffuse: 拡散反射光の放射輝度
 *
 */
// normal: 正規化された物体面の法線ベクトル
// incident_direction: 正規化された入射方向ベクトル
static t_color	calc_radiance_(t_object *const me, t_vector cross_point, t_light light, t_color ambient)
{
	t_color			color;
	const t_color	ra = ambient;
	const t_color	rd = calc_radiance_diffuse(me, cross_point, light);
	const t_color	rs = calc_radiance_specular(me, cross_point, light);
	const t_color	radiance = ({
		color = color_add(ra, rd);
		color_add(color, rs);
	});

	return (radiance);
}

static t_vector	object_calc_normal_(t_object *const me, t_vector cross_point)
{
	(void)me;
	(void)cross_point;
	assert(0);
}
