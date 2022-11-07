/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:23 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:23 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/color.h"
#include "../include/material.h"
#include "../include/object.h"
#include "../include/private_object_method.h"

void	sphere_ctor(t_sphere *const me, t_sphere_attrs *attrs)
{
	static t_object_vtbl	vtbl = {
		.solve_ray_equation = &sphere_solve_ray_equation,
		.calc_normal = &sphere_calc_normal,
		.calc_bumpmap_normal = &sphere_calc_bumpmap_normal,
		.calc_color = &sphere_calc_color
	};

	object_ctor(&me->super, attrs->center, attrs->k_diffuse, attrs->k_specular);
	me->super.vptr = &vtbl;
	me->radius = attrs->radius;
}
