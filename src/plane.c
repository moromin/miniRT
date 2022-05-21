#include <math.h>
#include <printf.h>
#include "../include/object.h"

static double	solve_ray_equation_(t_object *me, t_ray ray);
static t_vector	calc_normal_(t_object *me, t_vector cross_point);
static t_vector	calc_bumpmap_normal_(t_object *me, t_vector cross_point);
static t_color	calc_color_(t_object *me_, t_vector cross_point);
static t_uv 	calc_uv(const t_plane *me, t_vector cross_point);

void	plane_ctor(
		t_plane *const me,
		t_vector center,
		t_vector normal,
		t_color diffuse_reflection_coefficient,
		t_color specular_reflection_coefficient)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &solve_ray_equation_,
			.calc_normal = &calc_normal_,
			.calc_bumpmap_normal = &calc_bumpmap_normal_,
			.calc_color = &calc_color_,
	};
	const t_vector 			eu = ({
		const t_vector	ey = vec_init(0, 1, 0);
		t_vector	baseu;

		if (vec_magnitude(vec_cross(me->normal, ey)) == 0)
			baseu = vec_init(1, 0, 0);
		else
			baseu = vec_normalize(vec_cross(me->normal, ey));
		baseu;
	});

	object_ctor(&me->super, center, diffuse_reflection_coefficient, specular_reflection_coefficient);
	me->super.vptr = &vtbl;
	me->normal = normal;
	me->eu = eu;
	me->ev = vec_cross(me->normal, eu);
}

/*
 * cross_point_vector = camera_vector + t * watching_direction_vector
 * inner_product((plane_vector - plane_center_vector), normal_vector) = 0
 * => cross_point_vector = plane_vectorで解くと
 * t = -1 * (inner_product(camera_vector, normal_vector)
 * 				- inner_product(plane_center_vector, normal_vector))
 * 		/ inner_vector(watching_direction_vector, normal_vector)
 */
double	solve_ray_equation_(t_object *const me_, t_ray ray)
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

static t_vector	calc_normal_(t_object *const me_, t_vector cross_point)
{
	(void)cross_point;
	return (((t_plane *)me_)->normal);
}

static t_vector	calc_bumpmap_normal_(t_object *const me_, t_vector cross_point)
{
	const t_plane	*me = (t_plane *)me_;
	t_uv 		uv = calc_uv(me, cross_point);
	const t_vector	tangent = get_vector_from_normal_map(uv.u, uv.v, &me->super.info);
	const t_vector	normal = tangent_to_model(tangent, me->eu, me->ev, calc_normal(me_, cross_point));

	return (normal);
}

static t_color	calc_color_(t_object *const me_, t_vector cross_point)
{
	const t_plane	*me = (t_plane *)me_;
	const t_color 	c = ({
		t_color c;
		if (me->super.info.flag & 1 << FLAG_CHECKER)
			c = ch_color_at(&me->super.info, calc_uv(me, cross_point));
		else if (me->super.info.flag & 1 << FLAG_TEXTURE)
			c = tx_color_at(&me->super.info, calc_uv(me, cross_point));
		else
			c = me->super.material.k_specular;
		c;
	});

	return (c);
}

static t_uv 	calc_uv(const t_plane *const me, t_vector cross_point)
{
	double	integer;
	t_uv	uv;

	uv.u = modf(vec_dot(vec_sub(cross_point, me->super.center), me->eu), &integer);
	uv.v = modf(vec_dot(vec_sub(cross_point, me->super.center), me->ev), &integer);
	if (uv.u < 0)
		uv.u = 1 + uv.u;
	if (uv.v < 0)
		uv.v = 1 + uv.v;
	return (uv);
}
