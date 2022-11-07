/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_method.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:22 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:22 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/object.h"
#include <math.h>

static t_uv	plane_calc_uv(const t_plane *me, t_vector cross_point);

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

t_vector	plane_calc_normal(t_object *const me_, t_vector cross_point)
{
	(void)cross_point;
	return (((t_plane *)me_)->normal);
}

t_vector	plane_calc_bumpmap_normal(t_object *const me_, t_vector cross_point)
{
	const t_plane	*me = (t_plane *)me_;
	const t_uv		uv = plane_calc_uv(me, cross_point);
	const t_vector	tangent
		= get_vector_from_normal_map(uv.u, uv.v, &me->super.info);
	const t_vector	normal = \
		tangent_to_model(tangent, me->eu, me->ev, \
				object_calc_normal(me_, cross_point));

	return (normal);
}

t_color	plane_calc_color(t_object *const me_, t_vector cross_point)
{
	const t_plane	*me = (t_plane *)me_;
	const t_color	c = ({\
		t_color c;
		if (me->super.info.flag & 1 << FLAG_CHECKER)
			c = ch_color_at(&me->super.info, plane_calc_uv(me, cross_point));
		else if (me->super.info.flag & 1 << FLAG_TEXTURE)
			c = tx_color_at(&me->super.info, plane_calc_uv(me, cross_point));
		else
			c = me->super.material.k_specular;
		c;
	});

	return (c);
}

t_uv	plane_calc_uv(const t_plane *const me, t_vector cross_point)
{
	t_uv	uv;

	uv.u = fmod(vec_dot(vec_sub(cross_point, me->super.center), me->eu), 1);
	uv.v = fmod(vec_dot(vec_sub(cross_point, me->super.center), me->ev), 1);
	if (uv.u < 0)
		uv.u = 1 + uv.u;
	if (uv.v < 0)
		uv.v = 1 + uv.v;
	return (uv);
}
