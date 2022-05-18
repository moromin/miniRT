#include <math.h>
#include "../include/object.h"

static double	plane_solve_ray_equation(t_object *me, t_ray ray);
static t_vector	plane_calc_normal(t_object *me, t_vector cross_point);
static t_color	plane_calc_color(t_object *me_, t_vector cross_point);

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

	if (vec_dot(ray.direction, me->normal) == 0)
		return (-1.0);
	t = -1 * (vec_dot(ray.start, me->normal)
			- vec_dot(me->super.center, me->normal))
		/ vec_dot(ray.direction, me->normal);
	return (t);
}

static t_vector	plane_calc_normal(t_object *const me_, t_vector cross_point)
{
	const t_plane	*me = (t_plane *)me_;
	const t_vector	baseu = ({
			const t_vector	ey = vec_init(0, 1, 0);
			t_vector	baseu;

			if (vec_magnitude(vec_cross(me->normal, ey)) == 0)
				baseu = vec_init(1, 0, 0);
			else
				baseu = vec_normalize(vec_cross(me->normal, ey));
			baseu;
	});
	const t_vector	basev = vec_cross(me->normal, baseu);
	const t_vector	normal = ({
		t_vector	n;
		if (me->super.material.flag & 1 << MFLAG_BUMPMAP)
		{
			const t_bumpmap	bm = *((t_bumpmap *)me_->image);
			double			integer;
			double			u;
			double			v;
			t_vector		tangent;

			u = modf(vec_dot(vec_sub(cross_point, me->super.center), baseu), &integer);
			v = modf(vec_dot(vec_sub(cross_point, me->super.center), basev), &integer);
			tangent = get_vector_from_normal_map(u, v, bm);
			n = tangent_to_model(tangent, baseu, basev, me->normal);
		}
		else
			n = me->normal;
		n;
	});
	(void)cross_point;

	return (normal);
}

static t_color	plane_calc_color(t_object *const me_, t_vector cross_point)
{
	const t_plane	*me = (t_plane *)me_;
	const t_vector	baseu = ({
			const t_vector	ey = vec_init(0, 1, 0);
			t_vector	baseu;

			if (vec_magnitude(vec_cross(me->normal, ey)) == 0)
				baseu = vec_init(1, 0, 0);
			else
				baseu = vec_normalize(vec_cross(me->normal, ey));
			baseu;
	});
	const t_vector	basev = vec_cross(me->normal, baseu);
	const t_color c = ({
		t_color c;
		if (me->super.material.flag & 1 << MFLAG_CHECKER)
		{
			double	integer;
			double	u;
			double	v;

			u = modf(vec_dot(vec_sub(cross_point, me->super.center), baseu), &integer);
			v = modf(vec_dot(vec_sub(cross_point, me->super.center), basev), &integer);
			c = ch_pattern_at(me->super.material, u, v);
		}
		else
			c = me->super.material.diffuse_reflection_coefficient;
		c;
	});

	return (c);
}
