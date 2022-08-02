#include <math.h>

#include "../include/color.h"
#include "../include/material.h"
#include "../include/math.h"
#include "../include/object.h"

static double	solve_ray_equation(t_object *me, t_ray ray);
static t_vector	calc_normal(t_object *me, t_vector cross_point);
static t_vector	calc_bumpmap_normal(t_object *me, t_vector cross_point);
static t_color	calc_color(t_object *me_, t_vector cross_point);
static t_uv		calc_uv(const t_sphere *me, t_vector cross_point);

void	sphere_ctor(t_sphere *const me, double radius, t_vector center,
			t_color k_diffuse, t_color k_specular)
{
	static t_object_vtbl	vtbl = {
			.solve_ray_equation = &solve_ray_equation,
			.calc_normal = &calc_normal,
			.calc_bumpmap_normal = &calc_bumpmap_normal,
			.calc_color = &calc_color
	};

	object_ctor(&me->super, center, k_diffuse, k_specular);
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
static double	solve_ray_equation(t_object *const me_, t_ray ray)
{
	const t_sphere	*me = (t_sphere *)me_;
	const double	res = ({
			const double	a = vec_magnitude_squared(ray.direction);
			if (a == 0)
				return (-1.0);
			const double	b = 2 * (vec_dot(ray.start, ray.direction)
								 - vec_dot(ray.direction, me->super.center));
			const double	c = vec_magnitude_squared(ray.start)
								+ vec_magnitude_squared(me->super.center)
								- 2 * vec_dot(ray.start, me->super.center)
								- pow(me->radius, 2);
			const double	d = pow(b, 2) - 4 * a * c;
			const double	t_positive = (-1 * b + sqrt(d)) / (2 * a);
			const double	t_negative = (-1 * b - sqrt(d)) / (2 * a);

			if (d < 0 || (t_positive < 0 && t_negative < 0))
				return (-1.0);
			else if (t_positive < 0)
				return (t_negative);
			else if (t_negative < 0)
				return (t_positive);
			min(t_positive, t_negative);
	});

	return (res);
}

static t_vector	calc_normal(t_object *const me_, t_vector cross_point)
{
	const t_sphere	*me = (t_sphere *)me_;
	const t_vector	normal = ({
		const t_vector	center2cross = vec_sub(cross_point, me->super.center);
		vec_normalize(center2cross);
	});

	return (normal);
}

static t_vector	calc_bumpmap_normal(t_object *const me_, t_vector cross_point)
{
	const t_sphere	*me = (t_sphere *)me_;
	const t_vector	normal = ({
		const t_uv		uv = calc_uv(me, cross_point);
		const t_vector	tangent =
				get_vector_from_normal_map(uv.u, uv.v, &me->super.info);

		const t_vector	n = object_calc_normal(me_, cross_point);
		t_vector		t;
		const t_vector	ey = vec_init(0, 1, 0);
		if (vec_dot(n, ey) == 1)
			t = vec_init(1, 0, 0);
		else
			t = vec_normalize(vec_cross(n, ey));
		const t_vector	b = vec_normalize(vec_cross(t, n));

		tangent_to_model(tangent, t, b, n);
	});

	return (normal);
}

static t_color	calc_color(t_object *const me_, t_vector cross_point)
{
	const t_sphere	*me = (t_sphere *)me_;
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

static t_uv	calc_uv(const t_sphere *const me, t_vector cross_point)
{
	const t_uv	uv = ({
		t_uv	uv;
		const t_vector	center2cross = vec_sub(cross_point, me->super.center);
		const double	phi = atan2(center2cross.x, center2cross.z);
		const double	theta = acos(center2cross.y / me->radius);

		uv.u = 1 - (phi / (2 * M_PI) + 0.5);
		uv.v = theta / M_PI;
		uv;
	});

	return (uv);
}
