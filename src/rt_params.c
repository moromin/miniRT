#include "../include/scene.h"
#include "../minilibx-linux/mlx.h"

char	*load_ambient(t_program *p, char **info)
{
	double		ratio;
	t_color		c;

	if (!(ft_strtod(info[0], &ratio) && 0.0 <= ratio && ratio <= 1.0))
		return (ERR_MISCONFIGURED_AMBIENT);
	if (get_color_from_str(info[1], &c) && check_color_range(c, 0.0, 255.0))
		p->ambient = ambient(color_mult(color_mult(c, (double)1/255), ratio));
	else
		return (ERR_MISCONFIGURED_AMBIENT);
	return (NO_ERR);
}

char	*load_camera(t_program *p, char **info)
{
	double		fov;

	if (!get_vector_from_str(info[0], &p->camera.pos))
		return (ERR_MISCONFIGURED_CAMERA);
	if (!(get_vector_from_str(info[1], &p->camera.normal)
			&& check_vector_range(p->camera.normal, -1.0, 1.0)))
		return (ERR_MISCONFIGURED_CAMERA);
	if (vec_magnitude_squared(p->camera.normal) != 1)
	{
		ft_putendl_fd(WARNING_NOT_NORMALIZED, STDERR_FILENO);
		p->camera.normal = vec_normalize(p->camera.normal);
	}
	if (ft_strtod(info[2], &fov) && 0.0 <= fov && fov <= 180.0)
		p->camera.fov = fov;
	else
		return (ERR_MISCONFIGURED_CAMERA);
	return (NO_ERR);
}

char	*load_light(t_program *p, char **info)
{
	const t_slice	*light = ({
		t_slice		*l = make(sizeof(t_light), 1, 1);
		t_vector	pos;
		double		ratio;
		t_color		c;

		if (!get_vector_from_str(info[0], &pos))
			return (ERR_MISCONFIGURED_LIGHT);
		if (!(ft_strtod(info[1], &ratio) && 0.0 <= ratio && ratio <= 1.0))
			return (ERR_MISCONFIGURED_LIGHT);
		if (!(get_color_from_str(info[2], &c) && check_color_range(c, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_LIGHT);
		light_ctor(get(l, 0), pos, color_mult(color_mult(c, (double)1/255), ratio));
		l;
	});

	append(p->lights, &light);
	return (NO_ERR);
}


char	*load_spotlight(t_program *p, char **info)
{
	const	t_slice *spotlight = ({
			t_slice		*sp = make(sizeof(t_spotlight), 1, 1);
			t_vector	pos;
			t_vector	dir;
			double		fov;
			double		ratio;
			t_color		c;

			if (!get_vector_from_str(info[0], &pos))
				return (ERR_MISCONFIGURED_SPOTLIGHT);
			if (!get_vector_from_str(info[1], &dir))
				return (ERR_MISCONFIGURED_SPOTLIGHT);
			if (!(ft_strtod(info[2], &fov) && 0.0 <= fov && fov <= 360))
				return (ERR_MISCONFIGURED_SPOTLIGHT);
			if (!(ft_strtod(info[3], &ratio) && 0.0 <= ratio && ratio <= 1.0))
				return (ERR_MISCONFIGURED_SPOTLIGHT);
			if (!(get_color_from_str(info[4], &c) && check_color_range(c, 0.0, 255.0)))
				return (ERR_MISCONFIGURED_SPOTLIGHT);
			spotlight_ctor(get(sp, 0), pos, color_mult(color_mult(c, (double)1/255), ratio), dir, fov);
			sp;
	});

	append(p->lights, &spotlight);
	return (NO_ERR);
}

char	*load_checker(t_program *p, char **info)
{
	t_object	*object;
	t_color		c;

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->material.flag == (1 << MFLAG_CHECKER))
		return (ERR_DUPLICATE_MATERIAL);
	object->material.flag |= (1 << MFLAG_CHECKER);
	if (!(atoi_strict(info[0], &object->material.checker_width) && 1 <= object->material.checker_width))
		return (ERR_MISCONFIGURED_CHECKER);
	printf("%d\n", object->material.checker_width);
	if (!(atoi_strict(info[1], &object->material.checker_height) && 1 <= object->material.checker_height))
		return (ERR_MISCONFIGURED_CHECKER);
	printf("%d\n", object->material.checker_height);
	if (!(get_color_from_str(info[2], &c) && check_color_range(c, 0.0, 255.0)))
		return (ERR_MISCONFIGURED_CHECKER);
	object->material.checker_col1 = color_mult(c, (double)1/255);
	if (!(get_color_from_str(info[3], &c) && check_color_range(c, 0.0, 255.0)))
		return (ERR_MISCONFIGURED_CHECKER);
	object->material.checker_col2 = color_mult(c, (double)1/255);
	return (NO_ERR);
}

char	*load_bumpmap(t_program *p, char **info)
{
	t_object	*object;
	t_bumpmap	*bm;
	t_img		image;

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->material.flag == (1 << MFLAG_BUMPMAP))
		return (ERR_DUPLICATE_MATERIAL);
	object->material.flag |= (1 << MFLAG_BUMPMAP);

	// TODO: mlx error handling or wrapping
	bm = x_malloc(sizeof(t_bumpmap));
	image.image = mlx_xpm_file_to_image(p->mlx, info[0], &image.width, &image.height);
	if (!image.image)
		return (ERR_MISCONFIGURED_BUMPMAP);
	image.buffer = mlx_get_data_addr(image.image, &image.bits_per_pixel, &image.size_line, &image.endian);
	if (!image.buffer)
		return (ERR_MISCONFIGURED_BUMPMAP);
	bm->super = image;

	if (!(atoi_strict(info[1], &bm->freq_u) && 1 <= bm->freq_u))
		return (ERR_MISCONFIGURED_BUMPMAP);
	if (!(atoi_strict(info[2], &bm->freq_v) && 1 <= bm->freq_v))
		return (ERR_MISCONFIGURED_BUMPMAP);

	object->image = (t_img *)bm;
	return (NO_ERR);
}
