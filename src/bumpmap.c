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

			t_color	h1 = get_color_from_image(&bm.super, (int)i, (int)j);
			t_color	h2 = get_color_from_image(&bm.super, (int)i, (int)(j + 1) % bm.super.width);
			t_color	h3 = get_color_from_image(&bm.super, (int)(i + 1) % bm.super.height, (int)j);
			t_color	h4 = get_color_from_image(&bm.super, (int)(i + 1) % bm.super.height, (int)(j + 1) % bm.super.width);

			h1 = color_add(color_mult(h1, 2), color(-1, -1, -1));
			h2 = color_add(color_mult(h2, 2), color(-1, -1, -1));
			h3 = color_add(color_mult(h3, 2), color(-1, -1, -1));
			h4 = color_add(color_mult(h4, 2), color(-1, -1, -1));
			const t_color	sum = color_add(color_add(h1, h2), color_add(h3, h4));

			n = convert_color_to_vector(sum);
			n;
	});

	return (normal);
}

t_vector	tangent_to_model(t_vector tangent, t_vector t, t_vector b, t_vector n)
{
	const t_vector	normal = ({
			t_vector	res;


			res.x = vec_inner_product(vec_init(t.x, b.x, n.x), tangent);
			res.y = vec_inner_product(vec_init(t.y, b.y, n.y), tangent);
			res.z = vec_inner_product(vec_init(t.z, b.z, n.z), tangent);
			res = vec_normalize(res);
			res;
	});

	return (normal);
}
