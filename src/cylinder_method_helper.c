/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_method_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:21 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:21 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../include/object.h"

double	cylinder_solve_ray_equation_helper(
	t_ray ray,
	double t_outer,
	double t_inner,
	const t_cylinder *me)
{
	const double	res = ({
		double			res;
		const t_vector	outer =
			vec_add(ray.start, vec_mult(ray.direction, t_outer));
		const t_vector	inner =
			vec_add(ray.start, vec_mult(ray.direction, t_inner));
		const t_vector	center2outer = vec_sub(outer, me->super.center);
		const t_vector	center2inner = vec_sub(inner, me->super.center);
		const double	outer_height = vec_dot(center2outer, me->normal);
		const double	inner_height = vec_dot(center2inner, me->normal);
		if (t_outer >= 0.0 && 0.0 <= outer_height && outer_height <= me->height)
			res = t_outer;
		else if (t_inner >= 0.0 && 0.0 <= inner_height
				&& inner_height <= me->height)
			res = t_inner;
		else
			res = -1.0;
		res;
	});

	return (res);
}
