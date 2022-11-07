/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:01:46 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:01:46 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_with_error_message(const char *msg)
{
	ft_putendl_fd("ERROR", STDERR_FILENO);
	if (errno == 0)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	exit(EXIT_FAILURE);
}
