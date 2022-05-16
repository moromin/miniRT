#include <math.h>
#include <printf.h>

#include "../include/material.h"
#include "../include/color.h"
#include "../include/math.h"
#include "../include/object.h"

static double	sphere_solve_ray_equation(t_object *me, t_ray ray);
static t_vector	sphere_calc_normal(t_object *me, t_vector cross_point);
static t_color	sphere_calc_color(t_object *me_, t_vector cross_point);

		void	sphere_ctor(t_sphere *const me, double radius, t_vector center,
			t_color diffuse_reflection_coefficient, t_color specular_reflection_coefficient)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &sphere_solve_ray_equation,
			.calc_radiance = &calc_radiance_,
			.calc_normal = &sphere_calc_normal,
			.calc_color = &sphere_calc_color
	};

	object_ctor(&me->super, center, diffuse_reflection_coefficient, specular_reflection_coefficient);
	me->super.vptr = &vtbl;
	me->radius = radius;
}

/*
 * typedef struct s_ray {
 *  // 視点位置
 * 	t_vector start;
 *  // 視点位置からスクリーン点(x,y)に向かう半直線
 *  t_vector direction;
 * }
 * watching_vector = camera_vector + t * watching_direction_vector
 * abs(sphere_vector - sphere_center_vector) ^ 2 = radius ^ 2
 * => watching_vector = sphere_vectorで得と
 * t = (-B +- sqrt(B^2 - 4AC)) / 2A
 * A = magnitude(watching_direction_vector) ^ 2
 * B = 2 * (inner_product(camera_vector, watching_direction_vector)
 * 		- inner_product(watching_direction_vector, sphere_center_vector))
 * C = magnitude(camera_vector) ^ 2 + magnitude(sphere_center_vector) ^ 2
 * 		- 2 * (inner_product(camera_vector, sphere_center_vector)
 */
static double	sphere_solve_ray_equation(t_object *const me_, t_ray ray)
{
	const t_sphere	*me = (t_sphere *)me_;
	const double	t = ({
			const double	a = vec_magnitude_squared(ray.direction);
			if (a == 0)
				return (-1.0);
			const double	b = 2 * (vec_inner_product(ray.start, ray.direction)
									 - vec_inner_product(ray.direction, me->super.center));
			const double	c = vec_magnitude_squared(ray.start)
								+ vec_magnitude_squared(me->super.center)
								- 2 * vec_inner_product(ray.start, me->super.center)
								- pow(me->radius, 2);
			const double	d = pow(b, 2) - 4 * a * c;
			const double	t_positive = (-1 * b + sqrt(d)) / (2 * a);
			const double	t_negative = (-1 * b - sqrt(d)) / (2 * a);
			double			res;

			if (d < 0 || (t_positive < 0 && t_negative < 0))
				res = -1.0;
			else if (t_positive < 0)
				res = t_negative;
			else if (t_negative < 0)
				res = t_positive;
			else
				res = min(t_positive, t_negative);
			res;
	});

	return (t);
}

static t_vector	sphere_calc_normal(t_object *const me, t_vector cross_point)
{
	t_vector		vec;
	const t_vector	normal = ({
		vec = vec_sub(cross_point, me->center);
		vec_normalize(vec);
	});

	return (normal);
}

static t_color	sphere_calc_color(t_object *const me_, t_vector cross_point)
{
	const t_sphere	*me = (t_sphere *)me_;
	const t_color c = ({
		t_color c;
		if (me->super.material.flag & 1 << MFLAG_CHECKER)
		{
			const t_vector	p = vec_sub(cross_point, me->super.center);
			const double	u = 1 - (atan2(p.x, p.z) / (2 * M_PI) + 0.5);
			const double	v = 1 - acos(p.y / me->radius) / M_PI;

			c = ch_pattern_at(me->super.material, u, v);
		}
		else
			c = me->super.material.diffuse_reflection_coefficient;
		c;
	});

	return (c);
}
