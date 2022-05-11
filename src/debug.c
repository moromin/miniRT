#include "../include/vector.h"
#include "../include/color.h"

#include <stdio.h>

void	vec_print(t_vector v)
{
	printf("X: %f\t", v.x);
	printf("Y: %f\t", v.y);
	printf("Z: %f\t", v.z);
}

void	color_print(t_color c)
{
	printf("R: %f\t", c.r);
	printf("G: %f\t", c.g);
	printf("B: %f\t", c.b);
}
