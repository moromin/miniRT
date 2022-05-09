#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"

// todo: this should be input from rt file
# define WIDTH 512
# define HEIGHT 512

typedef struct s_program {
	void	*mlx;
	void	*win;
}	t_program;

typedef struct s_img {
	void	*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*buffer;
}	t_img;

typedef struct s_ray {
	// 視点位置
	t_vector	start;
	// 視点位置からスクリーン点(x,y)に向かう半直線
	t_vector	direction;
}	t_ray;

// todo: create its header file when there are more funcs
// image.c
void	init_image(t_program *program, t_img *img);
void	add_color_to_image(t_img *img, int color, int x, int y);

#endif
