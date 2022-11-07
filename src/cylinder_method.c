/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_method.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:21 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:21 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../include/color.h"
#include "../include/material.h"
#include "../include/math.h"
#include "../include/object.h"
#include "../include/private_object_method.h"

static t_uv	cylinder_calc_uv(const t_cylinder *const me, t_vector cross_point);

double	cylinder_solve_ray_equation(t_object *me_, t_ray ray)
{
	const t_cylinder	*me = (t_cylinder *)me_;
	const double		t = ({
		const double	a =
				vec_magnitude_squared(vec_cross(ray.direction, me->normal));
		if (a == 0)
			return (-1.0);
		const double	b = 2 * (vec_dot(
				vec_cross(ray.direction, me->normal),
				vec_cross(vec_sub(ray.start, me->super.center), me->normal)));
		const double	c = vec_magnitude_squared(vec_cross(
				vec_sub(ray.start, me->super.center),
				me->normal)) - pow(me->radius, 2);
		const double	d = pow(b, 2) - 4 * a * c;
		const double	t_inner = (-1 * b + sqrt(d)) / (2 * a);
		const double	t_outer = (-1 * b - sqrt(d)) / (2 * a);
		double			res;
		if (d < 0 || (t_inner < 0 && t_outer < 0))
			res = -1.0;
		else
			res = cylinder_solve_ray_equation_helper(ray, t_outer, t_inner, me);
		res;
	});

	return (t);
}

t_vector	cylinder_calc_normal(t_object *const me_, t_vector cross_point)
{
	const t_cylinder	*me = (t_cylinder *)me_;
	const t_vector		normal = ({
		const t_vector	center2cross =
				vec_sub(cross_point, me->super.center);
		const double	h = vec_dot(center2cross, me->normal);

		vec_normalize(vec_sub(center2cross, vec_mult(me->normal, h)));
	});

	return (normal);
}

t_vector	cylinder_calc_bumpmap_normal(
	t_object *const me_,
	t_vector cross_point)
{
	const t_cylinder	*me = (t_cylinder *)me_;
	const t_vector		normal = ({
		const t_uv		uv = cylinder_calc_uv(me, cross_point);
		const t_vector	tangent =
			get_vector_from_normal_map(uv.u, uv.v, &me->super.info);
		const t_vector	n = object_calc_normal(me_, cross_point);
		const t_vector	b = me->normal;
		const t_vector	t = vec_cross(b, n);

		tangent_to_model(tangent, t, b, n);
	});

	return (normal);
}

t_color	cylinder_calc_color(t_object *const me_, t_vector cross_point)
{
	const t_cylinder	*me = (t_cylinder *)me_;
	const t_color		c = ({
		t_color c;
		if (me->super.info.flag & 1 << FLAG_CHECKER)
			c = ch_color_at(&me->super.info, cylinder_calc_uv(me, cross_point));
		else if (me->super.info.flag & 1 << FLAG_TEXTURE)
			c = tx_color_at(&me->super.info, cylinder_calc_uv(me, cross_point));
		else
			c = me->super.material.k_diffuse;
		c;
	});

	return (c);
}

t_uv	cylinder_calc_uv(const t_cylinder *const me, t_vector cross_point)
{
	const t_uv	uv = ({
		t_uv	uv;
		const t_vector	n_center2cross =
				vec_normalize(vec_sub(cross_point, me->super.center));
		const double theta =
				M_PI / 2 - acos(vec_dot(n_center2cross, me->normal));
		const double height = tan(theta) * me->radius;
		uv.v = 1 - height / me->height;
		const double n1 = vec_dot(n_center2cross, me->e1);
		const double n2 = vec_dot(n_center2cross, me->e2);
		const double phi = atan2(n1, n2);
		uv.u = 1 - (phi / (2 * M_PI) + 0.5);
		uv;
	});

	return (uv);
}
