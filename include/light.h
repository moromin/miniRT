#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"

# define SHININESS 8
# define AMBIENT_REFLECTION_COEFFICIENT 0.01

typedef struct s_light {
	t_vector	pos;
	t_color		intensity;
//	t_color		color;
}	t_light;

t_light	light(t_vector coordinate, t_color intensity);
t_color	ambient(t_color intensity);

#endif //LIGHT_H
