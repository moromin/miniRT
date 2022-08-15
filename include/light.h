#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"
# include "vector.h"

# define SHININESS 8
# define AMBIENT_REFLECTION_COEFFICIENT 0.01

typedef struct s_light_vtbl	t_light_vtbl;

typedef struct s_light {
	t_light_vtbl	*vptr;
	t_vector		pos;
	t_color			intensity;
}	t_light;

void	light_ctor(t_light *me, t_vector pos, t_color intensity);

struct s_light_vtbl {
	bool	(*is_reachable)(t_light * const me, t_vector incident_dir);
};

bool	light_is_reachable(t_light *me, t_vector incident_dir);

typedef struct s_spotlight {
	t_light		super;
	t_vector	direction;
	double		fov;
}	t_spotlight;

typedef struct s_spotlight_attrs {
	t_vector	pos;
	t_color		intensity;
	t_vector	direction;
	double		fov;
}	t_spotlight_attrs;

void	spotlight_ctor(
			t_spotlight *me,
			t_spotlight_attrs *attrs
			);

t_color	ambient(t_color intensity);

#endif //LIGHT_H
