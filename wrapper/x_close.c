/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_close.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:02:11 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:11 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x.h"

void	x_close(int fd)
{
	int	res;

	res = close(fd);
	if (res == -1)
		exit_with_error_message("close");
}
