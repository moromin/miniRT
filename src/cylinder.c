/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:21 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:21 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/object.h"
#include "../include/private_object_method.h"

void	cylinder_ctor(t_cylinder *me, t_cylinder_attrs *attrs)
{
	static t_object_vtbl	vtbl = {\
		.solve_ray_equation = &cylinder_solve_ray_equation,
		.calc_normal = &cylinder_calc_normal,
		.calc_bumpmap_normal = &cylinder_calc_bumpmap_normal,
		.calc_color = &cylinder_calc_color,
	};
	const t_vector			e1 = ({\
		const t_vector	ex = vec_init(1, 0, 0);
		t_vector		vec;
		if (vec_dot(attrs->normal, ex) == 1)
			vec = ex;
		else
			vec = vec_cross(attrs->normal, ex);
		vec;
	});

	object_ctor(&me->super, attrs->center, attrs->k_diffuse, attrs->k_specular);
	me->super.vptr = &vtbl;
	me->radius = attrs->radius;
	me->height = attrs->height;
	me->normal = attrs->normal;
	me->e1 = e1;
	me->e2 = vec_cross(e1, me->normal);
}
