#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "ray.h"
# include "color.h"
# include "light.h"
# include "material.h"
# include "obj_info.h"

// Object
typedef struct s_object_vtbl	t_object_vtbl;

typedef struct s_object {
	t_object_vtbl	*vptr;
	t_vector		center;
	t_material		material;
	t_obj_info		info;
}	t_object;

/* Object's operations (Object's interface)... */
void		object_ctor(
				t_object *me,
				t_vector center,
				t_color diffuse_reflection_coefficient,
				t_color specular_reflection_coefficient);
double		object_solve_ray_equation(t_object *me, t_ray ray);
t_vector	object_calc_normal(t_object *me, t_vector cross_point);
t_vector	object_calc_bumpmap_normal(t_object *me, t_vector cross_point);
t_color		object_calc_color(t_object *me, t_vector cross_point);

// Virtual table
struct s_object_vtbl {
	double		(*solve_ray_equation)(t_object *const me, t_ray);
	t_vector	(*calc_normal)(t_object * const me, t_vector);
	t_vector	(*calc_bumpmap_normal)(t_object * const me, t_vector);
	t_color		(*calc_color)(t_object * const me, t_vector cross_point);
};

t_color		calc_radiance(
				t_object *me,
				t_vector cross_point,
				t_light light,
				t_vector camera_dir);

// sphere
typedef struct s_sphere {
	t_object	super;
	double		radius;
}	t_sphere;

typedef struct s_sphere_attrs {
	double		radius;
	t_vector	center;
	t_color		k_diffuse;
	t_color		k_specular;
}	t_sphere_attrs;

void		sphere_ctor(
				t_sphere *me,
				t_sphere_attrs *attrs);

// plane
typedef struct s_plane {
	t_object	super;
	t_vector	normal;
	t_vector	eu;
	t_vector	ev;
}	t_plane;

typedef struct s_plane_attrs {
	t_vector	center;
	t_vector	normal;
	t_color		k_diffuse;
	t_color		k_specular;
}	t_plane_attrs;

void		plane_ctor(
				t_plane *me,
				t_plane_attrs *attrs);

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
				t_color k_diffuse,
				t_color k_specular);

// cone
typedef struct s_cone
{
	t_object	super;
	t_vector	normal;
	double		aperture;
	t_vector	e1;
	t_vector	e2;
}	t_cone;

typedef struct s_cone_attrs
{
	t_vector	center;
	t_vector	normal;
	double		aperture;
	t_color		k_diffuse;
	t_color		k_specular;
}	t_cone_attrs;

void		cone_ctor(t_cone *me, t_cone_attrs attrs);

#endif
