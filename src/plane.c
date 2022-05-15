#include <math.h>
#include "../include/object.h"

static double	plane_solve_ray_equation(t_object *me, t_ray ray);
static t_vector	plane_calc_normal(t_object *me, t_vector cross_point);
static t_color	plane_calc_color(t_object *const me_, t_vector cross_point);

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
			.calc_normal = &plane_calc_normal,
			.calc_color = &plane_calc_color,
	};

	object_ctor(&me->super, center, diffuse_reflection_coefficient, specular_reflection_coefficient);
	me->super.vptr = &vtbl;
	me->normal = normal;
	me->super.material.checker_height = 2;
	me->super.material.checker_width = 2;
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

static t_color	plane_calc_color(t_object *const me_, t_vector cross_point)
{
	const t_plane	*me = (t_plane *)me_;
	const t_vector	baseu = ({
			const t_vector	ey = vec_init(0, 1, 0);
			t_vector	baseu;

			if (vec_magnitude(vec_outer_product(me->normal, ey)) == 0)
				baseu = vec_init(1, 0, 0);
			else
				baseu = vec_normalize(vec_outer_product(me->normal, ey));
			baseu;
	});
	const t_vector	basev = vec_outer_product(me->normal, baseu);
	const t_color c = ({
		t_color c;
		if (me->super.material.material_flag & 1 << MFLAG_CHECKER)
		{
			double	integer;
			double	u;
			double	v;

			u = modf(vec_inner_product(vec_sub(cross_point, me->super.center), baseu), &integer);
			v = modf(vec_inner_product(vec_sub(cross_point, me->super.center), basev), &integer);
			c = ch_pattern_at(me->super.material, u, v);
		}
		else
			c = me->super.material.diffuse_reflection_coefficient;
		c;
	});

	return (c);
}