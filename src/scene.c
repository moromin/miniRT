/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:23 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:23 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scene.h"
#include "../include/free.h"
#include "../minilibx-linux/mlx.h"

static bool	check_filename(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension == NULL)
		return (false);
	if (ft_strcmp(extension, ".rt"))
		return (false);
	return (true);
}

void	load_rt_file(int argc, char **argv, t_program *p)
{
	char	*err;

	if (argc != 2)
		exit_with_error_message(ERR_INVALID_ARGS);
	if (!check_filename(argv[1]))
		exit_with_error_message(ERR_INVALID_FILE);
	err = read_rt_file(argv[1], p);
	if (err != NO_ERR)
	{
		destroy_object_images(p);
		delete_recursively(p->lights, 1);
		delete_recursively(p->objects, 1);
		mlx_destroy_display(p->mlx);
		exit_with_error_message(err);
	}
}
