#include <assert.h>

#include "../include/object.h"
#include "../include/miniRT.h"
#include "../include/light.h"

static double	object_solve_ray_equation_(t_object *me, t_ray ray);
static int		object_raytrace_(
					t_object *me, t_vector cross_point, t_vector light);

void	object_ctor(t_object *const me, t_vector center)
{
	static t_object_vtbl	vtbl = {
			&object_solve_ray_equation_,
			&object_raytrace_
	};

	me->vptr = &vtbl;
	me->center = center;
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
static int	object_raytrace_(
		t_object *me_, t_vector cross_point, t_vector light_point)
{
	const t_sphere	*me = (t_sphere*)me_;
	double			radiance;

	radiance = calc_radiance(me->super.center, cross_point, light_point);
	return (rgb_to_int(radiance, radiance, radiance));
}

double	object_solve_ray_equation(t_object *const me, t_ray ray)
{
	return ((*me->vptr->solve_ray_equation)(me, ray));
}

int	object_raytrace(t_object *me, t_vector cross_point, t_vector light)
{
	return ((*me->vptr->raytrace)(me, cross_point, light));
}
