/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_2d_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:01:46 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:01:46 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	count_2d_array(void **array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
