/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_open.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:02:11 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:11 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x.h"

int	x_open(const char *path, int mode)
{
	int	fd;

	fd = open(path, mode);
	if (fd == -1)
		exit_with_error_message("open");
	return (fd);
}
