#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "miniRT.h"

// Object
/* forward declaration */
typedef struct s_object_vtbl	t_object_vtbl;
/* Object's attributes... */
typedef struct s_object {
	t_object_vtbl const	*vptr; /* <== Object's Virtual Pointer */
//	int16_t x; /* x-coordinate of Object's position */
//	int16_t y; /* y-coordinate of Object's position */
}	t_object;

/* Shape's operations (Shape's interface)... */
void	object_ctor(t_object *me);
double	object_intersect_at(t_object *me, t_ray ray);

// Virtual table
struct s_object_vtbl {
	double	(*intersect_at)(t_object *const me, t_ray ray);
};

// sphere
typedef struct s_sphere {
	/* <== inherits Shape */
	t_object	super;
	/* attributes added by this subclass... */
	double		radius;
	t_vector	center; // described as pc
}	t_sphere;

void	sphere_ctor(t_sphere *me, double radius, t_vector center);

#endif
