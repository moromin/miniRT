#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"

// Object
/* forward declaration */
typedef struct s_object_vtbl	t_object_vtbl;
/* Object's attributes... */
typedef struct s_object {
	t_object_vtbl	*vptr; /* <== Object's Virtual Pointer */
	t_vector		center; // described as pc
}	t_object;

/* Shape's operations (Shape's interface)... */
void	object_ctor(t_object *me, t_vector center);
double	object_solve_ray_equation(t_object *me, t_ray ray);
int		object_raytrace(t_object *me, t_vector cross_point, t_vector light);

// Virtual table
struct s_object_vtbl {
	double	(*solve_ray_equation)(t_object *const me, t_ray ray);
	int		(*raytrace)(t_object *const me,
			t_vector cross_point, t_vector light);
};

// sphere
typedef struct s_sphere {
	/* <== inherits Shape */
	t_object	super;
	/* attributes added by this subclass... */
	double		radius;
}	t_sphere;

void	sphere_ctor(t_sphere *me, double radius, t_vector center);

#endif
