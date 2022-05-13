#include <math.h>
#include <printf.h>
#include "../include/color.h"
#include "../include/vector.h"
#include "../include/light.h"
#include "../include/object.h"

t_color	calc_radiance_diffuse(t_object *obj, t_vector cross_point, t_light light, t_vector camera2cross)
{
	t_vector		vec;
	const t_vector	normal = ({
			t_vector n = object_calc_normal(obj, cross_point);
			if (vec_inner_product(n, camera2cross) > 0)
				n = vec_mult(n, -1);
			n;
	});
//	const t_vector	normal = object_calc_normal(obj, cross_point);
	const t_vector	incident_direction = ({
		vec = vec_sub(light.pos, cross_point);
		vec_normalize(vec);
	});

	if (vec_inner_product(normal, incident_direction) >= 0)
	{
		return (color_mult(color_prod(obj->diffuse_reflection_coefficient, light.intensity), vec_inner_product(normal, incident_direction)));
	}
	else
		return (color(0, 0, 0));
}

// specular: 入射光の正反射ベクトル
t_color	calc_radiance_specular(t_object *obj, t_vector cross_point, t_light light, t_vector camera2cross)
{
	t_vector		vec;
	const t_vector	normal = ({
		t_vector n = object_calc_normal(obj, cross_point);
		if (vec_inner_product(n, camera2cross) > 0)
			n = vec_mult(n, -1);
		n;
	});
//	const t_vector	normal = object_calc_normal(obj, cross_point);
	const t_vector	incident_direction = ({
		vec = vec_sub(light.pos, cross_point);
		vec_normalize(vec);
	});
	const t_vector	specular = ({
		vec = vec_mult(normal, 2 * vec_inner_product(normal, incident_direction));
		vec_sub(vec, incident_direction);
	});
	const t_vector	cross_point_inverse_normalized = ({
		vec = vec_mult(camera2cross, -1);
		vec_normalize(vec);
	});

	if (vec_inner_product(normal, incident_direction) >= 0 && vec_inner_product(vec, specular) >= 0)
		return (color_mult(color_prod(obj->specular_reflection_coefficient, light.intensity),
				   pow(vec_inner_product(cross_point_inverse_normalized, specular), SHININESS)));
	else
		return (color(0, 0, 0));
}
