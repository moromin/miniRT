/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:02:11 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:11 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x.h"

void	*x_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		exit_with_error_message("malloc");
	return (res);
}
