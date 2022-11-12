/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_radiance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:22 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:22 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/color.h"
#include "../include/vector.h"
#include "../include/light.h"
#include "../include/object.h"

static t_color	calc_radiance_diffuse(
					t_object *obj,
					t_vector cross_point,
					t_light light,
					t_vector camera2cross);
static t_color	calc_radiance_specular(
					t_object *obj,
					t_vector cross_point,
					t_light light,
					t_vector camera2cross);

/*
 * radiance_ambient: 環境光の反射光の放射輝度
 * radiance_specular: 直接光の鏡面反射光の放射輝度
 * radiance_diffuse: 拡散反射光の放射輝度
 *
 */
// normal: 正規化された物体面の法線ベクトル
// incident_direction: 正規化された入射方向ベクトル
t_color	calc_radiance(
			t_object *const me,
			t_vector cross_point,
			t_light light,
			t_vector camera2cross)
{
	const t_color	rd
		= calc_radiance_diffuse(me, cross_point, light, camera2cross);
	const t_color	rs
		= calc_radiance_specular(me, cross_point, light, camera2cross);

	return (color_add(rd, rs));
}

static t_color	calc_radiance_diffuse(
					t_object *obj,
					t_vector cross_point,
					t_light light,
					t_vector camera2cross)
{
	t_vector		vec;
	const t_vector	normal = ({\
		t_vector n;
		if (obj->info.flag & (1 << FLAG_BUMPMAP))
			n = object_calc_bumpmap_normal(obj, cross_point);
		else
			n = object_calc_normal(obj, cross_point);
		if (vec_dot(n, camera2cross) > 0)
			n = vec_mult(n, -1);
		n;
	});
	const t_vector	incident_direction = ({\
		vec = vec_sub(light.pos, cross_point);
		vec_normalize(vec);
	});
	const t_color	col = object_calc_color(obj, cross_point);

	if (vec_dot(normal, incident_direction) >= 0)
		return (color_mult(color_prod(col, light.intensity), \
					vec_dot(normal, incident_direction)));
	else
		return (color(0, 0, 0));
}

// specular: 入射光の正反射ベクトル
static t_color	calc_radiance_specular(
		t_object *obj,
		t_vector cross_point,
		t_light light,
		t_vector camera2cross)
{
	const t_vector	normal = ({\
		t_vector n;
		if (obj->info.flag & (1 << FLAG_BUMPMAP))
			n = object_calc_bumpmap_normal(obj, cross_point);
		else
			n = object_calc_normal(obj, cross_point);
		if (vec_dot(n, camera2cross) > 0)
			n = vec_mult(n, -1);
		n;
	});
	const t_vector	incident_direction
		= vec_normalize(vec_sub(light.pos, cross_point));
	const t_vector	specular
		= vec_sub(vec_mult(normal, 2 * vec_dot(normal, incident_direction)),
			incident_direction);
	const t_vector	cross_point_inverse_normalized
		= vec_normalize(vec_mult(camera2cross, -1));

	if (vec_dot(normal, incident_direction) >= 0
		&& vec_dot(cross_point_inverse_normalized, specular) >= 0)
		return (color_mult(\
			color_prod(obj->material.k_specular, light.intensity), \
			pow(vec_dot(cross_point_inverse_normalized, specular), SHININESS)));
	return (color(0, 0, 0));
}
