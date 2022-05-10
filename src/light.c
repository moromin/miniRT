#include "../include/vector.h"
#include "../include/light.h"

t_light	light(t_vector coordinate, t_color intensity)
{
	const t_light	l = {
			.coordinate = coordinate,
			.intensity = intensity,
	};

	return (l);
}

t_ambient	ambient(t_color intensity, t_color reflection_coefficient)
{
	const t_ambient	a = {
			.reflection_coefficient = reflection_coefficient,
			.intensity = intensity,
	};

	return (a);
}
