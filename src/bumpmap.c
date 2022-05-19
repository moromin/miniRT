#include "math.h"
#include "../include/miniRT.h"
#include "../include/vector.h"
#include "../include/material.h"
#include "../minilibx-linux/mlx.h"

static t_vector		convert_color_to_vector(t_color c)
{
	t_vector	rtn;

	rtn.x = c.r;
	rtn.y = c.b;
	rtn.z = c.g;
	return (rtn);
}

t_vector	get_vector_from_normal_map(double u, double v, const t_obj_info *info)
{
	const t_vector	tangent = ({
			const double	j = fmod(u * info->bm_freq_u, 1.0) * info->bm_image.width;
			const double	i = fmod(v * info->bm_freq_v, 1.0) * info->bm_image.height;

			t_color	c = get_color_from_image(&info->bm_image, (int)j, (int)i);
			c = color_add(color_mult(c, 2), color(-1, -1, -1));
			convert_color_to_vector(c);
	});

	return (tangent);
}

t_vector	tangent_to_model(t_vector tangent, t_vector t, t_vector b, t_vector n)
{
	const t_vector	normal = ({
			t_vector	res;

			res = vec_add(vec_add(
				vec_mult(t, tangent.x),
				vec_mult(b, tangent.z)),
				vec_mult(n, tangent.y));
			res = vec_normalize(res);
			res;
	});

	return (normal);
}
