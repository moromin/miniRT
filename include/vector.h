#ifndef VECTOR_H
# define VECTOR_H

# include <stdbool.h>

# define X 0
# define Y 1
# define Z 2

typedef struct s_vector {
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	vec_add(t_vector v1, t_vector v2);

t_vector	vec_mult(t_vector v, double k);

// todo: rm this if it is not used
void		vec_copy(t_vector *dest, t_vector src);

t_vector	vec_sub(t_vector v1, t_vector v2);

double		vec_inner_product(t_vector v1, t_vector v2);

t_vector	vec_outer_product(t_vector v1, t_vector v2);

double		vec_magnitude(t_vector v);

double		vec_magnitude_squared(t_vector v);

t_vector	vec_normalize(t_vector v);

t_vector	vec_init(double x, double y, double z);

void		vec_print(t_vector v);

// vector_utils.c
bool		get_vector_from_str(char *params, t_vector *v);
bool		check_vector_range(t_vector v, double min, double max);

#endif
