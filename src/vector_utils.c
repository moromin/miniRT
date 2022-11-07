/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:23 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:23 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.h"
#include "../utils/utils.h"
#include "../wrapper/x.h"

bool	get_vector_from_str(char *params, t_vector *v)
{
	char	**xyz;
	bool	is_valid;

	xyz = x_split(params, ',');
	if (count_2d_array((void **)xyz) != 3)
	{
		free_2d_array((void ***)&xyz);
		return (false);
	}
	is_valid = (ft_strtod(xyz[X], &v->x)
			&& ft_strtod(xyz[Y], &v->y)
			&& ft_strtod(xyz[Z], &v->z));
	free_2d_array((void ***)&xyz);
	return (is_valid);
}

bool	check_vector_range(t_vector v, double min, double max)
{
	const bool	x_ok = (min <= v.x && v.x <= max);
	const bool	y_ok = (min <= v.y && v.y <= max);
	const bool	z_ok = (min <= v.z && v.z <= max);

	return (x_ok && y_ok && z_ok);
}
