#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"

# define SHININESS 8
# define SHININESS 8

typedef struct s_light {
	t_vector	coordinate;
	t_color		intensity;
//	t_color		color;
}	t_light;

typedef struct s_ambient {
	t_color		intensity;
	t_color		reflection_coefficient;
}	t_ambient;

t_light		light(t_vector coordinate, t_color intensity);
t_ambient	ambient(t_color intensity, t_color reflection_coefficient);

#endif //LIGHT_H
