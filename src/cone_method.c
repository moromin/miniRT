#include <math.h>

#include "../include/color.h"
#include "../include/material.h"
#include "../include/math.h"
#include "../include/object.h"

static t_uv	cone_calc_uv(const t_cone *const me, t_vector cross_point);

double	cone_solve_ray_equation(t_object *const me_, t_ray ray)
{
	const t_cone	*me = (t_cone *)me_;
	const double	t = ({
		double			res;
		const double	k = cos(me->aperture / 2 / 180 * M_PI);
		const t_vector	q = vec_sub(ray.start, me->super.center);
		const t_vector	B = vec_mult(ray.direction, k);
		const t_vector	Q = vec_mult(q, k);
		const double	R = vec_dot(ray.direction, me->normal);
		const double	S = vec_dot(q, me->normal);
		const double	a = vec_magnitude_squared(B) - pow(R, 2);
		const double	b = 2 * (vec_dot(B, Q) - R * S);
		const double	c = vec_magnitude_squared(Q) - pow(S, 2);
		const double	d = pow(b, 2) - 4 * a * c;
		if (a == 0) return (-1 * c / b);
		else if (d < 0)	return (-1.0);
		double			t_outer = (-1 * b - sqrt(d)) / (2 * a);
		double			t_inner = (-1 * b + sqrt(d)) / (2 * a);
		if (t_outer < 0) t_outer = INFINITY;
		if (t_inner < 0) t_inner = INFINITY;
		if (t_outer == INFINITY && t_inner == INFINITY)	res = -1.0;
		else res = min(t_outer, t_inner);
		res;
	});

	return (t);
}

t_vector	cone_calc_normal(t_object *me_, t_vector cross_point)
{
	const t_cone	*me = (t_cone *)me_;
	const t_vector	normal = ({
		t_vector		direction = me->normal;
		const t_vector	center_to_cross =
				vec_normalize(vec_sub(cross_point, me->super.center));

		if (vec_dot(center_to_cross, direction) < 0)
			direction = vec_mult(direction, -1);
		vec_normalize(vec_sub(vec_mult(\
			center_to_cross, cos(me->aperture / 2 / 180 * M_PI)), direction));
	});

	return (normal);
}

t_vector	cone_calc_bumpmap_normal(
	t_object *const me_,
	t_vector cross_point)
{
	const t_cone	*me = (t_cone *)me_;
	const t_vector	normal = ({
		t_uv			uv = cone_calc_uv(me, cross_point);
		const t_vector	tangent =
				get_vector_from_normal_map(uv.u, uv.v, &me->super.info);

		t_vector		direction = me->normal;
		if (vec_dot(vec_sub(cross_point, me->super.center), direction) < 0)
			direction = vec_mult(direction, -1);

		const t_vector	n = object_calc_normal(me_, cross_point);
		const t_vector	t = vec_normalize(vec_cross(direction, n));
		const t_vector	b = vec_normalize(vec_cross(t, n));

		tangent_to_model(tangent, t, b, n);
	});

	return (normal);
}

t_color	cone_calc_color(t_object *const me_, t_vector cross_point)
{
	const t_cone	*me = (t_cone *)me_;
	const t_color	c = ({
		t_color c;
		if (me->super.info.flag & 1 << FLAG_CHECKER)
			c = ch_color_at(&me->super.info, cone_calc_uv(me, cross_point));
		else if (me->super.info.flag & 1 << FLAG_TEXTURE)
			c = tx_color_at(&me->super.info, cone_calc_uv(me, cross_point));
		else
			c = me->super.material.k_diffuse;
		c;
	});

	return (c);
}

t_uv	cone_calc_uv(const t_cone *const me, t_vector cross_point)
{
	const t_uv	uv = ({
		t_uv	uv;
		double	integer;
		const t_vector	center2cross = vec_sub(cross_point, me->super.center);
		uv.v = modf(vec_dot(center2cross, me->normal), &integer);
		const double n1 = vec_dot(center2cross, me->e1);
		const double n2 = vec_dot(center2cross, me->e2);
		const double phi = atan2(n1, n2);
		uv.u = phi / (2 * M_PI) + 0.5;
		if (uv.v < 0)
			uv.v *= -1;
		uv;
	});

	return (uv);
}
