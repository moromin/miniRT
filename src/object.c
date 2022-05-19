#include <assert.h>
#include <printf.h>

#include "../include/object.h"

static double	object_solve_ray_equation_(t_object *me, t_ray ray);
static t_vector	object_calc_normal_(t_object *me, t_vector cross_point);
static t_vector	object_calc_bumpmap_normal_(t_object *me, t_vector cross_point);
static t_color	calc_color_(t_object *me, t_vector cross_point);

void	object_ctor(t_object *const me, t_vector center,
			t_color k_diffuse, t_color k_specular)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &object_solve_ray_equation_,
			.calc_radiance = &calc_radiance_,
			.calc_normal = &object_calc_normal_,
			.calc_bumpmap_normal = &object_calc_bumpmap_normal_,
			.calc_color = &calc_color_,
	};
	const t_obj_info	info = {
			.flag = 0
	};
	const t_material	material = {
			.k_diffuse = k_diffuse,
			.k_specular = k_specular,
	};

	me->vptr = &vtbl;
	me->center = center;
	me->material = material;
	me->info = info;
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
t_color	calc_radiance_(t_object *const me, t_vector cross_point, t_light light, t_vector camera2cross)
{
	const t_color	rd = calc_radiance_diffuse(me, cross_point, light, camera2cross);
	const t_color	rs = calc_radiance_specular(me, cross_point, light, camera2cross);

	return (color_add(rd, rs));
}

static t_vector	object_calc_normal_(t_object *const me, t_vector cross_point)
{
	(void)me;
	(void)cross_point;
	assert(0);
}

static t_vector	object_calc_bumpmap_normal_(t_object *const me, t_vector cross_point)
{
	(void)me;
	(void)cross_point;
	assert(0);
}

static t_color	calc_color_(t_object *me, t_vector cross_point)
{
	(void)me;
	(void)cross_point;
	assert(0);
}
