/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:24 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:12 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "object.h"
# include "color.h"
# include "light.h"
# include "camera.h"
# include "slice.h"
# include "image.h"

// todo: this should be input from rt file
# define WIDTH 512
# define HEIGHT 512
# define SCREEN_WIDTH 2
# define SCREEN_HEIGHT 2

//# define EPSILON (1.0 / 512)
# define EPSILON 0.000001

typedef struct s_program {
	void		*mlx;
	void		*win;
	t_img		img;
	t_slice		*lights;
	t_color		ambient;
	t_slice		*objects;
	t_camera	camera;
}	t_program;

// todo: create its header file when there are more funcs
// create_image.c
void		create_image(t_program *program);

// image.c
void		init_image(t_program *program, t_img *img);
void		add_color_to_image(t_img *img, t_color color, int x, int y);
t_color		get_color_from_image(const t_img *img, int x, int y);

// utils.c
int			rgb_to_int(double r, double g, double b);

#endif
