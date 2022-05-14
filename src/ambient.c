#include "../include/color.h"
#include "../include/light.h"

t_color	ambient(t_color intensity)
{
	return (color_mult(intensity, AMBIENT_REFLECTION_COEFFICIENT));
}
