/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_object_method.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:24 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:12 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// cylinder methods
double		cylinder_solve_ray_equation(t_object *me, t_ray ray);
t_vector	cylinder_calc_normal(t_object *me, t_vector cross_point);
t_vector	cylinder_calc_bumpmap_normal(t_object *me, t_vector cross_point);
t_color		cylinder_calc_color(t_object *me, t_vector cross_point);
double		cylinder_solve_ray_equation_helper(
				t_ray ray,
				double t_outer,
				double t_inner,
				const t_cylinder *me);

// cone methods
double		cone_solve_ray_equation(t_object *me, t_ray ray);
t_vector	cone_calc_normal(t_object *me, t_vector cross_point);
t_vector	cone_calc_bumpmap_normal(t_object *me, t_vector cross_point);
t_color		cone_calc_color(t_object *me, t_vector cross_point);

#endif
