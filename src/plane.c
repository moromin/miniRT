#include "../include/object.h"

static double	plane_solve_ray_equation(t_object *me, t_ray ray);
static t_vector	plane_calc_normal(t_object *me, t_vector cross_point);

void	plane_ctor(
		t_plane *const me,
		t_vector center,
		t_vector normal,
		t_color diffuse_reflection_coefficient,
		t_color specular_reflection_coefficient)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &plane_solve_ray_equation,
			.calc_radiance = &calc_radiance_,
			.calc_normal = &plane_calc_normal
	};

	object_ctor(&me->super, center, diffuse_reflection_coefficient, specular_reflection_coefficient);
	me->super.vptr = &vtbl;
	me->normal = normal;
}

/*
 * cross_point_vector = camera_vector + t * watching_direction_vector
 * inner_product((plane_vector - plane_center_vector), normal_vector) = 0
 * => cross_point_vector = plane_vectorで解くと
 * t = -1 * (inner_product(camera_vector, normal_vector)
 * 				- inner_product(plane_center_vector, normal_vector))
 * 		/ inner_vector(watching_direction_vector, normal_vector)
 */
double	plane_solve_ray_equation(t_object *const me_, t_ray ray)
{
	const t_plane	*me = (t_plane *)me_;
	double			t;

	if (vec_inner_product(ray.direction, me->normal) == 0)
		return (-1.0);
	t = -1 * (vec_inner_product(ray.start, me->normal)
			- vec_inner_product(me->super.center, me->normal))
		/ vec_inner_product(ray.direction, me->normal);
	return (t);
}

static t_vector	plane_calc_normal(t_object *const me, t_vector cross_point)
{
	(void)cross_point;
	return (((t_plane *)me)->normal);
}
