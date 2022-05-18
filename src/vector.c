#include "../include/vector.h"

#include <math.h>

t_vector	vec_add(t_vector v1, t_vector v2)
{
	t_vector	rtn;

	rtn.x = v1.x + v2.x;
	rtn.y = v1.y + v2.y;
	rtn.z = v1.z + v2.z;
	return (rtn);
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	t_vector	rtn;

	rtn.x = v1.x - v2.x;
	rtn.y = v1.y - v2.y;
	rtn.z = v1.z - v2.z;
	return (rtn);
}

t_vector	vec_mult(t_vector v, double k)
{
	t_vector	rtn;

	rtn.x = v.x * k;
	rtn.y = v.y * k;
	rtn.z = v.z * k;
	return (rtn);
}

t_vector	vec_init(double x, double y, double z)
{
	t_vector	rtn;

	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}
