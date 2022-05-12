#include "../include/vector.h"
#include "../include/light.h"

t_light	light(t_vector coordinate, t_color intensity)
{
	const t_light	l = {
			.pos = coordinate,
			.intensity = intensity,
	};

	return (l);
}

t_color	ambient(t_color intensity)
{
	return (color_mult(intensity, AMBIENT_REFLECTION_COEFFICIENT));
}
