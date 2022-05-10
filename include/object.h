#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "color.h"
# include "light.h"

// Object
/* forward declaration */
typedef struct s_object_vtbl	t_object_vtbl;
/* Object's attributes... */
typedef struct s_object {
	t_object_vtbl	*vptr; /* <== Object's Virtual Pointer */
	t_vector		center; // described as pc
	t_color			diffuse_reflection_coefficient;
	t_color			specular_reflection_coefficient;
}	t_object;

/* Shape's operations (Shape's interface)... */
void		object_ctor(t_object *me, t_vector center, t_color diffuse_reflection_coefficient, t_color specular_reflection_coefficient);
double		object_solve_ray_equation(t_object *me, t_ray ray);
t_color		object_calc_radiance(t_object *me, t_vector cross_point, t_light light, t_ambient amb);
t_vector	object_calc_normal(t_object *me, t_vector cross_point);

// Virtual table
struct s_object_vtbl {
	double		(*solve_ray_equation)(t_object *const me, t_ray ray);
	t_color		(*calc_radiance)(t_object * const me, t_vector cross_point, t_light light, t_ambient amb);
	t_vector	(*calc_normal)(t_object * const me, t_vector cross_point);
};

// sphere
typedef struct s_sphere {
	/* <== inherits Shape */
	t_object	super;
	/* attributes added by this subclass... */
	double		radius;
}	t_sphere;

void		sphere_ctor(t_sphere *me, double radius, t_vector center, t_color diffuse_reflection_coefficient, t_color specular_reflection_coefficient);
t_color		calc_radiance_diffuse(t_object *obj, t_vector cross_point, t_light light);
t_color		calc_radiance_specular(t_object *obj, t_vector cross_point, t_light light);

#endif
