/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:22 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:22 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <printf.h>

#include "../include/object.h"

static double	solve_ray_equation_(t_object *me, t_ray ray);
static t_vector	calc_normal_(t_object *me, t_vector cross_point);
static t_vector	calc_bumpmap_normal_(t_object *me, t_vector cross_point);
static t_color	calc_color_(t_object *me, t_vector cross_point);

void	object_ctor(t_object *const me, t_vector center,
			t_color k_diffuse, t_color k_specular)
{
	static t_object_vtbl	vtbl = {
		.solve_ray_equation = &solve_ray_equation_,
		.calc_normal = &calc_normal_,
		.calc_bumpmap_normal = &calc_bumpmap_normal_,
		.calc_color = &calc_color_,
	};
	const t_obj_info		info = {
		.flag = 0
	};
	const t_material		material = {
		.k_diffuse = k_diffuse,
		.k_specular = k_specular,
	};

	me->vptr = &vtbl;
	me->center = center;
	me->material = material;
	me->info = info;
}

static double	solve_ray_equation_(t_object *const me, t_ray ray)
{
	(void)me;
	(void)ray;
	assert(0);
}

static t_vector	calc_normal_(t_object *const me, t_vector cross_point)
{
	(void)me;
	(void)cross_point;
	assert(0);
}

static t_vector	calc_bumpmap_normal_(t_object *const me, t_vector cross_point)
{
	(void)me;
	(void)cross_point;
	assert(0);
}

static t_color	calc_color_(t_object *me, t_vector cross_point)
{
	(void)me;
	(void)cross_point;
	assert(0);
}
