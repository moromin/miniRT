/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:22 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:22 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../include/vector.h"
#include "../include/miniRT.h"
#include "../include/scene.h"
#include "../include/mlx_hooks.h"

// camera_point described as pe
int	main(int argc, char **argv)
{
	t_program	program;

	program.mlx = mlx_init();
	load_rt_file(argc, argv, &program);
	program.win = mlx_new_window(program.mlx, WIDTH, HEIGHT, "miniRT");
	init_image(&program, &program.img);
	create_image(&program);
	mlx_put_image_to_window(program.mlx, program.win, program.img.image, 0, 0);
	set_mlx_hooks(&program);
	mlx_loop(program.mlx);
}
