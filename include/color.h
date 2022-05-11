#ifndef COLOR_H
# define COLOR_H

# include <stdbool.h>

# define RED 0
# define GREEN 1
# define BLUE 2

typedef struct s_color {
	double	r;
	double	g;
	double	b;
}	t_color;

// color.c
int		color_to_int(t_color color);
t_color	color(double r, double g, double b);
t_color	color_add(t_color c1, t_color c2);
t_color	color_mult(t_color c, double k);
t_color	color_prod(t_color c1, t_color c2);

// color_utils.c
bool	get_color_from_str(char *params, t_color *color);
t_color	color_map(t_color c);

#endif
