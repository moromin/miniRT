/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:02:11 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:11 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x.h"

char	**x_split(const char *s, char c)
{
	char	**split;

	split = ft_split(s, c);
	if (!split)
		exit_with_error_message("malloc");
	return (split);
}
