#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "object.h"

// todo: this should be input from rt file
# define WIDTH 512
# define HEIGHT 512

typedef struct s_img	t_img;

struct s_img {
	void	*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*buffer;
};

typedef struct s_program {
	void		*mlx;
	void		*win;
	t_img		img;
	t_vector	camera_point;
	t_vector	light_point;
	t_object	object;
}	t_program;

// todo: create its header file when there are more funcs
// image.c
void		init_image(t_program *program, t_img *img);
void		add_color_to_image(t_img *img, int color, int x, int y);

// camera.c
t_vector	init_camera_point(void);

// utils.c
int			rgb_to_int(double r, double g, double b);

#endif
