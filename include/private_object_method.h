#ifndef PRIVATE_OBJECT_METHOD_H
# define PRIVATE_OBJECT_METHOD_H

// plane methods
double		plane_solve_ray_equation(t_object *me, t_ray ray);
t_vector	plane_calc_normal(t_object *me, t_vector cross_point);
t_vector	plane_calc_bumpmap_normal(t_object *me, t_vector cross_point);
t_color		plane_calc_color(t_object *me_, t_vector cross_point);

// sphere methods
double		sphere_solve_ray_equation(t_object *me, t_ray ray);
t_vector	sphere_calc_normal(t_object *me, t_vector cross_point);
t_vector	sphere_calc_bumpmap_normal(t_object *me, t_vector cross_point);
t_color		sphere_calc_color(t_object *me_, t_vector cross_point);

// cone methods
double		cone_solve_ray_equation(t_object *me, t_ray ray);
t_vector	cone_calc_normal(t_object *me, t_vector cross_point);
t_vector	cone_calc_bumpmap_normal(t_object *me, t_vector cross_point);
t_color		cone_calc_color(t_object *me, t_vector cross_point);

#endif
