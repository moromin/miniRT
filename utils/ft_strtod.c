/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:01:46 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:01:46 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_strtod(const char *s, double *val)
{
	double	converted;
	double	sign;
	int		fract;

	sign = 1.0;
	converted = 0.0;
	while (ft_isspace(*s))
		s++;
	if ((*s == '+' || *s == '-') && *s++ == '-')
		sign = -1.0;
	if (*s == '\0')
		return (false);
	while (ft_isdigit(*s))
		converted = converted * 10.0 + *s++ - '0';
	*val = sign * converted;
	if (*s == '\0')
		return (true);
	else if (*s == '.' && *(++s) == '\0')
		return (false);
	fract = 1;
	while (ft_isdigit(*s))
		converted += pow(0.1, fract++) * (*s++ - '0');
	*val = sign * converted;
	return (*s == '\0');
}
