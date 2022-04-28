#include "../include/miniRT.h"

void vec_print(t_vector v)
{
	for (int i = 0; i < v.dim; i++) {
		printf("%f\t", v.comp[i]);
	}
}

t_vector* vec_add(t_vector v1, t_vector v2)
{
	t_vector *rtn;

	if (v1.dim != v2.dim)
		return NULL;
	if (!(rtn = malloc(sizeof(t_program))))
		return NULL;
	if (!(rtn->comp = malloc(sizeof(double) * v1.dim)))
		return NULL;
	for (int i = 0; i < v1.dim; i++) {
		rtn->comp[i] = v1.comp[i] + v2.comp[i];
//		printf("v1: %f\tv2: %f\trtn: %f\n", v1.comp[i], v2.comp[i], rtn->comp[i]);
	}
	rtn->dim = v1.dim;
	return rtn;
}

t_vector* vec_sub(t_vector v1, t_vector v2)
{
	t_vector *rtn;

	if (v1.dim != v2.dim)
		return NULL;
	if (!(rtn = malloc(sizeof(t_program))))
		return NULL;
	if (!(rtn->comp = malloc(sizeof(double) * v1.dim)))
		return NULL;
	for (int i = 0; i < v1.dim; i++) {
		rtn->comp[i] = v1.comp[i] - v2.comp[i];
	}
	rtn->dim = v1.dim;
	return rtn;
}

t_vector* vec_mult(t_vector v, int k)
{
	t_vector *rtn;

	if (!(rtn = malloc(sizeof(t_program))))
		return NULL;
	if (!(rtn->comp = malloc(sizeof(double) * v.dim)))
		return NULL;
	for (int i = 0; i < v.dim; i++) {
		rtn->comp[i] = v.comp[i] * k;
	}
	rtn->dim = v.dim;
	return rtn;
}

void vec_copy(t_vector *dest, t_vector src)
{
	if (dest->dim != src.dim)
		return ;
	for (int i = 0; i < dest->dim; i++) {
		dest->comp[i] = src.comp[i];
	}
}

double vec_in_pro(t_vector v1, t_vector v2)
{
	double rtn;

	rtn = 0;
	if (v1.dim != v2.dim)
		return (0);
	for (int i = 0; i < v1.dim; i++) {
		rtn += v1.comp[i] * v2.comp[i];
	}
	return rtn;
}

t_vector* vec_out_pro(t_vector v1, t_vector v2)
{
	t_vector *rtn;

	if (v1.dim != v2.dim) {
		write(2, "error\n", 6);
		return (0);
	}
	if (v1.dim != 3) {
		printf("this is N dimensional");
		return (0);
	}
	if (!(rtn = malloc(sizeof(t_program))))
		return NULL;
	if (!(rtn->comp = malloc(sizeof(double) * v1.dim)))
		return NULL;
	rtn->dim = 3;
	rtn->comp[0] = (v1.comp[1] * v2.comp[2]) - (v1.comp[2] * v2.comp[1]);
	rtn->comp[1] = (v1.comp[2] * v2.comp[0]) - (v1.comp[0] * v2.comp[2]);
	rtn->comp[2] = (v1.comp[0] * v2.comp[1]) - (v1.comp[1] * v2.comp[0]);
	return rtn;
}

double vec_mag_sq(t_vector v)
{
	return pow(v.comp[0], 2) + pow(v.comp[1], 2) + pow(v.comp[2], 2);
}