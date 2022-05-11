#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "object.h"
# include "color.h"
# include "light.h"

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
	t_light		*lights;
	int			light_count;
	t_color		ambient;
	t_object	**objects;
}	t_program;

// todo: create its header file when there are more funcs
// image.c
void		init_image(t_program *program, t_img *img);
void		add_color_to_image(t_img *img, int color, int x, int y);

// utils.c
int			rgb_to_int(double r, double g, double b);

#endif
