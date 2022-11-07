/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_strict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:01:45 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:01:45 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	atoi_strict(char *str, int *dst)
{
	long long	rtn;
	int			sign;

	rtn = 0;
	sign = 1;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (false);
	while ('0' <= *str && *str <= '9')
	{
		if ((rtn * 10 + *str - '0') / 10 != rtn)
			return (false);
		rtn = rtn * 10 + *str - '0';
		str++;
	}
	*dst = (int)(sign * rtn);
	if (*str == '\0')
		return (true);
	return (false);
}
