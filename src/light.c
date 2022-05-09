#include <math.h>
#include "../include/vector.h"
#include "../include/light.h"
#include "../include/math.h"

t_vector	init_light_point(void)
{
	return (vec_init(-5, 5, -5));
}

double	calc_radiance_diffuse(
			t_vector center, t_vector cross_point, t_vector light_point)
{
	t_vector		vec;
	const t_vector	normal = ({
		vec = vec_sub(cross_point, center);
		vec_normalize(vec);
	});
	const t_vector	incident_direction = ({
		vec = vec_sub(light_point, cross_point);
		vec_normalize(vec);
	});
	double			radiance_diffuse;

	radiance_diffuse = 0;
	if (vec_inner_product(normal, incident_direction) > 0)
		radiance_diffuse = vec_inner_product(normal, incident_direction)
			* DIFFUSE_REFLECTION_COEFFICIENT * LIGHT_INTENSITY;
	return (radiance_diffuse);
}

double	calc_radiance_specular(
			t_vector center, t_vector cross_point, t_vector light_point)
{
	t_vector		vec;
	double			radiance_specular;
	const t_vector	normal = ({
		vec = vec_sub(cross_point, center);
		vec_normalize(vec);
	});
	const t_vector	incident_direction = ({
		vec = vec_sub(light_point, cross_point);
		vec_normalize(vec);
	});
	const t_vector	specular = ({
		vec = vec_mult(normal, 2 * vec_inner_product(normal, incident_direction));
		vec_sub(vec, incident_direction);
	});

	radiance_specular = ({
			vec = vec_mult(cross_point, -1);
			vec = vec_normalize(vec);
			pow(vec_inner_product(vec, specular), SHININESS)
				* SPECULAR_REFLECTION_COEFFICIENT * LIGHT_INTENSITY;
	});
	radiance_specular = max(radiance_specular, 0);
	return (radiance_specular);
}

double	calc_radiance(
		t_vector center, t_vector cross_point, t_vector light_point)
{
	double	radiance;
	double	rd;
	double	ra;
	double	rs;

	ra = AMBIENT_REFLECTION_COEFFICIENT * AMBIENT_INTENSITY;
	rd = calc_radiance_diffuse(center, cross_point, light_point);
	rs = calc_radiance_specular(center, cross_point, light_point);
	radiance = ra + rd + rs;
	return (radiance);
}
