#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "color.h"
# include "light.h"
# include "material.h"
# include "obj_info.h"

// Object
/* forward declaration */
typedef struct s_object_vtbl	t_object_vtbl;

/* Object's attributes... */
typedef struct s_object {
	t_object_vtbl	*vptr; /* <== Object's Virtual Pointer */
	t_vector		center; // described as pc
	t_material		material;
	t_obj_info		info;
}	t_object;

/* Shape's operations (Shape's interface)... */
void		object_ctor(t_object *me, t_vector center, t_color diffuse_reflection_coefficient, t_color specular_reflection_coefficient);
double		object_solve_ray_equation(t_object *me, t_ray ray);
t_color		object_calc_radiance(t_object *me, t_vector cross_point, t_light light, t_vector camera_dir);
t_vector	object_calc_normal(t_object *me, t_vector cross_point);
t_vector	object_calc_bumpmap_normal(t_object *me, t_vector cross_point);
t_color		object_calc_color(t_object *me, t_vector cross_point);

// Virtual table
struct s_object_vtbl {
	double		(*solve_ray_equation)(t_object *const me, t_ray);
	t_color		(*calc_radiance)(t_object * const me, t_vector, t_light, t_vector);
	t_vector	(*calc_normal)(t_object * const me, t_vector);
	t_vector	(*calc_bumpmap_normal)(t_object * const me, t_vector);
	t_color		(*calc_color)(t_object * const me, t_vector cross_point);
};

t_color		calc_radiance_(t_object *me, t_vector cross_point, t_light light, t_vector camera_dir);
t_color		calc_radiance_diffuse(t_object *obj, t_vector cross_point, t_light light, t_vector camera_dir);
t_color		calc_radiance_specular(t_object *obj, t_vector cross_point, t_light light, t_vector camera_dir);

// sphere
typedef struct s_sphere {
	/* <== inherits Shape */
	t_object	super;
	/* attributes added by this subclass... */
	double		radius;
}	t_sphere;

void		sphere_ctor(t_sphere *me, double radius, t_vector center, t_color diffuse_reflection_coefficient, t_color specular_reflection_coefficient);

// plane
typedef struct s_plane {
	t_object	super;
	t_vector	normal;
	t_vector	eu;
	t_vector	ev;
}	t_plane;

void		plane_ctor(
				t_plane *me,
				t_vector center,
				t_vector normal,
				t_color diffuse_reflection_coefficient,
				t_color specular_reflection_coefficient);

// cylinder
typedef struct s_cylinder
{
	t_object	super;
	t_vector	normal;
	double		radius;
	double		height;
	t_vector	e1;
	t_vector	e2;
}	t_cylinder;

void		cylinder_ctor(
				t_cylinder *me,
				t_vector center,
				t_vector normal,
				double radius,
				double height,
				t_color diffuse_reflection_coefficient,
				t_color specular_reflection_coefficient);

// cone
typedef struct s_cone
{
	t_object	super;
	t_vector	normal;
	double		aperture;
	t_vector	e1;
	t_vector	e2;
}	t_cone;

void		cone_ctor(
				t_cone *me,
				t_vector center,
				t_vector normal,
				double aperture,
				t_color diffuse_reflection_coefficient,
				t_color specular_reflection_coefficient);

#endif
