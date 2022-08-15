#include "../include/object.h"
#include "../include/math.h"
#include "../include/obj_info.h"
#include <math.h>

static double	solve_ray_equation(t_object *me, t_ray ray);
static t_vector	calc_normal(t_object *me, t_vector cross_point);
static t_vector	calc_bumpmap_normal(t_object *me, t_vector cross_point);
static t_color	calc_color(t_object *me, t_vector cross_point);
static t_uv		calc_uv(const t_cone *me, t_vector cross_point);

void	cone_ctor(t_cone *me, t_cone_attrs attrs)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &solve_ray_equation,
			.calc_normal = &calc_normal,
			.calc_bumpmap_normal = &calc_bumpmap_normal,
			.calc_color = &calc_color,
	};
	const t_vector			e1 = ({
		const t_vector	ex = vec_init(1, 0, 0);
		t_vector	vec;
		if (vec_dot(attrs.normal, ex) == 1)
			vec = ex;
		else
			vec = vec_cross(attrs.normal, ex);
		vec;
	});

	object_ctor(&me->super, attrs.center, attrs.k_diffuse, attrs.k_specular);
	me->super.vptr = &vtbl;
	me->normal = attrs.normal;
	me->aperture = attrs.aperture;
	me->e1 = e1;
	me->e2 = vec_cross(e1, me->normal);
}

double	solve_ray_equation(t_object *const me_, t_ray ray)
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

			if (a == 0)
				return (-1 * c / b);
			else if (d < 0)
				return (-1.0);

			double			t_outer = (-1 * b - sqrt(d)) / (2 * a);
			double			t_inner = (-1 * b + sqrt(d)) / (2 * a);

			if (t_outer < 0)
				t_outer = INFINITY;
			if (t_inner < 0)
				t_inner = INFINITY;
			if (t_outer == INFINITY && t_inner == INFINITY)
				res = -1.0;
			else
				res = min(t_outer, t_inner);
			res;
	});

	return (t);
}

static t_vector	calc_normal(t_object *const me_, t_vector cross_point)
{
	const t_cone	*me = (t_cone *)me_;
	const t_vector	normal = ({
			t_vector		direction = me->normal;
			const t_vector	center_to_cross = vec_normalize(vec_sub(cross_point, me->super.center));

			if (vec_dot(center_to_cross, direction) < 0)
				direction = vec_mult(direction, -1);
			vec_normalize(vec_sub(vec_mult(center_to_cross, cos(me->aperture / 2 / 180 * M_PI)), direction));
	});

	return (normal);
}

static t_vector	calc_bumpmap_normal(t_object *const me_, t_vector cross_point)
{
	const t_cone	*me = (t_cone *)me_;
	const t_vector	normal = ({
			t_uv			uv = calc_uv(me, cross_point);
			const t_vector	tangent = get_vector_from_normal_map(uv.u, uv.v, &me->super.info);

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

static t_color	calc_color(t_object *const me_, t_vector cross_point)
{
	const t_cone	*me = (t_cone *)me_;
	const t_color	c = ({
		t_color c;
		if (me->super.info.flag & 1 << FLAG_CHECKER)
			c = ch_color_at(&me->super.info, calc_uv(me, cross_point));
		else if (me->super.info.flag & 1 << FLAG_TEXTURE)
			c = tx_color_at(&me->super.info, calc_uv(me, cross_point));
		else
			c = me->super.material.k_diffuse;
		c;
	});

	return (c);
}

static t_uv	calc_uv(const t_cone *const me, t_vector cross_point)
{
	const t_uv	uv = ({
		t_uv	uv;
		double	integer;
		const t_vector	center2cross = vec_sub(cross_point, me->super.center);
		// checkerの変数v (0 <= v <= 1)
		uv.v = modf(vec_dot(center2cross, me->normal), &integer);
		// 基底ベクトル1方向への大きさ（-pi <= n1 <= p1）
		const double n1 = vec_dot(center2cross, me->e1);
		const double n2 = vec_dot(center2cross, me->e2);
		// 方位角 (-pi < phi <= pi)
		const double phi = atan2(n1, n2);
		uv.u = phi / (2 * M_PI) + 0.5;
		if (uv.v < 0)
			uv.v *= -1;
		uv;
	});

	return (uv);
}
