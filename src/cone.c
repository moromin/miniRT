#include "../include/object.h"
#include "../include/math.h"
#include <math.h>

static double	cone_solve_ray_equation(t_object *me, t_ray ray);
static t_vector	cone_calc_normal(t_object *me, t_vector cross_point);

void	cone_ctor(
			t_cone *me,
			t_vector center,
			t_vector normal,
			double aperture,
			t_color diffuse_reflection_coefficient,
			t_color specular_reflection_coefficient)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &cone_solve_ray_equation,
			.calc_radiance = &calc_radiance_,
			.calc_normal = &cone_calc_normal
	};

	object_ctor(&me->super, center, diffuse_reflection_coefficient, specular_reflection_coefficient);
	me->super.vptr = &vtbl;
	me->normal = normal;
	me->aperture = aperture;
}

double	cone_solve_ray_equation(t_object *const me_, t_ray ray)
{
	const t_cone	*me = (t_cone *)me_;
	const double	t = ({
			double			res;

			const double	k = cos(me->aperture / 2 / 180 * M_PI);
			const t_vector	q = vec_sub(ray.start, me->super.center);

			const t_vector	B = vec_mult(ray.direction, k);
			const t_vector	Q = vec_mult(q, k);
			const double	R = vec_inner_product(ray.direction, me->normal);
			const double	S = vec_inner_product(q, me->normal);

			const double	a = vec_magnitude_squared(B) - pow(R, 2);
			const double	b = 2 * (vec_inner_product(B, Q) - R * S);
			const double	c = vec_magnitude_squared(Q) - pow(S, 2);
			const double	d = pow(b, 2) - 4 * a * c;

			if (a == 0)
				return (-1 * c / b);
			else if (d < 0)
				return (-1.0);

			double			t_outer = (-1 * b - sqrt(d)) / (2 * a);
			double			t_inner = (-1 * b + sqrt(d)) / (2 * a);

			// half cone
			// const t_vector	outer = vec_add(ray.start, vec_mult(ray.direction, t_outer));
			// const t_vector	inner = vec_add(ray.start, vec_mult(ray.direction, t_inner));

			// const double	outer_dir = vec_inner_product(vec_sub(outer, me->super.center), me->normal);
			// const double	inner_dir = vec_inner_product(vec_sub(inner, me->super.center), me->normal);

			// if (!(t_outer > 0 && outer_dir >= 0))
			// 	t_outer = INFINITY;
			// if (!(t_inner > 0 && inner_dir >= 0))
			// 	t_inner = INFINITY;

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

static t_vector	cone_calc_normal(t_object *const me_, t_vector cross_point)
{
	const t_cone	*me = (t_cone *)me_;
	const t_vector	normal = ({
			t_vector		res;
			t_vector		direction = me->normal;
			const t_vector	center_to_cross = vec_normalize(vec_sub(cross_point, me->super.center));

			if (vec_inner_product(center_to_cross, direction) < 0)
				direction = vec_mult(direction, -1);
			res = vec_normalize(vec_sub(vec_mult(center_to_cross, cos(me->aperture / 2 / 180 * M_PI)), direction));
			res;
	});

	return (normal);
}
