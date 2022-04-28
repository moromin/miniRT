#ifndef FT_MINIRT_MINIRT_H
# define FT_MINIRT_MINIRT_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>

// for debugging
# include <printf.h>

typedef struct	s_program
{
	void	*mlx;
	void	*win;
}				t_program;

typedef struct	s_vector
{
	double	*comp;
	int 	dim;
}				t_vector;

// vector.c
void		vec_print(t_vector v);
t_vector*	vec_add(t_vector v1, t_vector v2);
t_vector*	vec_mult(t_vector v, int k);
void		vec_copy(t_vector *dest, t_vector src);
t_vector* 	vec_sub(t_vector v1, t_vector v2);
double		vec_in_pro(t_vector v1, t_vector v2);
t_vector*	vec_out_pro(t_vector v1, t_vector v2);
double vec_mag_sq(t_vector v);

#endif