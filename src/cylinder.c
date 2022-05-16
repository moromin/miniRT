#include <math.h>
#include <printf.h>

#include "../include/object.h"
#include "../include/math.h"

static double	cylinder_solve_ray_equation(t_object *me, t_ray ray);
static t_vector	cylinder_calc_normal(t_object *me, t_vector cross_point);
static t_color	cylinder_calc_color(t_object *me, t_vector cross_point);

void	cylinder_ctor(
			t_cylinder *me,
			t_vector center,
			t_vector normal,
			double radius,
			double height,
			t_color diffuse_reflection_coefficient,
			t_color specular_reflection_coefficient)
{
	static t_object_vtbl	vtbl = {
		.solve_ray_equation = &cylinder_solve_ray_equation,
		.calc_radiance = &calc_radiance_,
		.calc_normal = &cylinder_calc_normal,
		.calc_color = &cylinder_calc_color,
	};

	object_ctor(&me->super, center, diffuse_reflection_coefficient, specular_reflection_coefficient);
	me->super.vptr = &vtbl;
	me->radius = radius;
	me->height = height;
	me->normal = normal;
}

double	cylinder_solve_ray_equation(t_object *me_, t_ray ray)
{
	const t_cylinder	*me = (t_cylinder *)me_;
	const double		t = ({
			const double	a = vec_magnitude_squared(vec_outer_product(ray.direction, me->normal));
			if (a == 0)
				return (-1.0);

			const double	b = 2 * (vec_inner_product(
										vec_outer_product(ray.direction, me->normal),
										vec_outer_product(vec_sub(ray.start, me->super.center), me->normal)));
			const double	c = vec_magnitude_squared(vec_outer_product(
										vec_sub(ray.start, me->super.center),
										me->normal)) - pow(me->radius, 2);
			const double	d = pow(b, 2) - 4 * a * c;
			const double	t_inner = (-1 * b + sqrt(d)) / (2 * a);
			const double	t_outer = (-1 * b - sqrt(d)) / (2 * a);
			double			res;

			if (d < 0 || (t_inner < 0 && t_outer < 0))
				res = -1.0;
			else
			{
				const t_vector	outer = vec_add(ray.start, vec_mult(ray.direction, t_outer));
				const t_vector	inner = vec_add(ray.start, vec_mult(ray.direction, t_inner));

				const t_vector	center_to_outer = vec_sub(outer, me->super.center);
				const t_vector	center_to_inner = vec_sub(inner, me->super.center);

				const double	outer_height = vec_inner_product(center_to_outer, me->normal);
				const double	inner_height = vec_inner_product(center_to_inner, me->normal);

				if (t_outer >= 0.0 && 0.0 <= outer_height && outer_height <= me->height)
					res = t_outer;
				else if (t_inner >= 0.0 && 0.0 <= inner_height && inner_height <= me->height)
					res = t_inner;
				else
					res = -1.0;
			}
			res;
	});

	return (t);
}

t_vector	cylinder_calc_normal(t_object *const me_, t_vector cross_point)
{
	const t_cylinder	*me = (t_cylinder *)me_;
	const t_vector		normal = ({
			const t_vector	center_to_cross = vec_sub(cross_point, me->super.center);
			const double	h = vec_inner_product(center_to_cross, me->normal);
			t_vector		m;

			m = vec_sub(center_to_cross, vec_mult(me->normal, h));
			m = vec_normalize(m);
			m;
	});

	return (normal);
}

static t_color	cylinder_calc_color(t_object *const me_, t_vector cross_point)
{
	const t_cylinder	*me = (t_cylinder *)me_;
	// normal方向以外の基底ベクトル
	const t_vector		e1 = ({
			const t_vector	ex = vec_init(1, 0, 0);
			t_vector	vec;
			if (vec_inner_product(me->normal, ex) == 1)
				vec = ex;
			else
				vec = vec_outer_product(me->normal, ex);
			vec;
	});
	const t_vector		e2 = vec_outer_product(e1, me->normal);
	const t_color c = ({
		t_color c;
		if (me->super.material.material_flag & 1 << MFLAG_CHECKER)
		{
			(void)cross_point;
			const t_vector	n_center_to_cross = vec_normalize(vec_sub(cross_point, me->super.center));
			// 仰角 (0 <= theta <= max_theta)
			const double theta = M_PI / 2 - acos(vec_inner_product(n_center_to_cross, me->normal));
			const double height = tan(theta) * me->radius;
			// checkerの変数v (0 <= v <= 1)
			const double v = height / me->height;
			// 基底ベクトル1方向への大きさ（-pi <= n1 <= p1）
			const double n1 = vec_inner_product(n_center_to_cross, e1);
			const double n2 = vec_inner_product(n_center_to_cross, e2);
			// 方位角 (-pi < phi <= pi)
			const double phi = atan2(n1, n2);
			const double u = phi / (2 * M_PI) + 0.5;
			c = ch_pattern_at(me->super.material, u, v);
		}
		else
			c = me->super.material.diffuse_reflection_coefficient;
		c;
	});
	return (c);
}
