#include "../include/vector.h"

#include <math.h>

double	vec_inner_product(t_vector v1, t_vector v2)
{
	double	rtn;

	rtn = v1.x * v2.x;
	rtn += v1.y * v2.y;
	rtn += v1.z * v2.z;
	return (rtn);
}

t_vector	vec_outer_product(t_vector v1, t_vector v2)
{
	t_vector	rtn;

	rtn.x = (v1.y * v2.z) - (v1.z * v2.y);
	rtn.y = (v1.z * v2.x) - (v1.x * v2.z);
	rtn.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (rtn);
}

double	vec_magnitude_squared(t_vector v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double	vec_magnitude(t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vector	vec_normalize(t_vector v)
{
	return (vec_mult(v, (1 / vec_magnitude(v))));
}
