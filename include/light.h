#ifndef LIGHT_H
# define LIGHT_H

# define AMBIENT_REFLECTION_COEFFICIENT 0.01
# define DIFFUSE_REFLECTION_COEFFICIENT 0.69
# define SPECULAR_REFLECTION_COEFFICIENT 0.3
# define AMBIENT_INTENSITY 0.1
# define LIGHT_INTENSITY 1.0
# define SHININESS 8

t_vector	init_light_point(void);
double		calc_radiance(
				t_vector center, t_vector cross_point, t_vector light_point);

#endif //LIGHT_H
