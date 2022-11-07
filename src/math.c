/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:22 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:22 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

double	min(double a, double b)
{
	if (a >= b)
		return (b);
	return (a);
}

double	max(double a, double b)
{
	if (a <= b)
		return (b);
	return (a);
}

bool	chmin(double *a, double b)
{
	if (*a > b)
	{
		*a = b;
		return (true);
	}
	return (false);
}
