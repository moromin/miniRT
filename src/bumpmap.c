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

static double	rt_fmod(double x, double y)
{
	if (x >= 0)
		return (fmod(x, y));
	else
		return (y - fmod(-x, y));
}

t_vector	get_vector_from_normal_map(double u, double v, t_bumpmap bm)
{
	const t_vector	normal = ({
			t_vector		n;
			const double	i = rt_fmod(u * bm.super.height * bm.freq_u, bm.super.height);
			const double	j = rt_fmod(v * bm.super.width * bm.freq_v, bm.super.width);

			t_color	c = get_color_from_image(&bm.super, (int)i, (int)j);
			c = color_add(color_mult(c, 2), color(-1, -1, -1));

			n = convert_color_to_vector(c);
			n;
	});

	return (normal);
}

t_vector	tangent_to_model(t_vector tangent, t_vector t, t_vector b, t_vector n)
{
	const t_vector	normal = ({
			t_vector	res;

			// 資料とy, z軸が逆！
			res = vec_add(vec_add(
				vec_mult(t, tangent.x),
				vec_mult(b, tangent.z)),
				vec_mult(n, tangent.y));
			res = vec_normalize(res);
			res;
	});

	return (normal);
}
