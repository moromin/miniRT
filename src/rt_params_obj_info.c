#include "../include/scene.h"
#include "../minilibx-linux/mlx.h"

char	*load_checker(t_program *p, char **info)
{
	t_object	*object;
	t_color		c;

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->material.flag & (1 << MFLAG_CHECKER))
		return (ERR_DUPLICATE_MATERIAL);
	object->material.flag |= (1 << MFLAG_CHECKER);
	if (!(atoi_strict(info[0], &object->material.checker_width) && 1 <= object->material.checker_width))
		return (ERR_MISCONFIGURED_CHECKER);
	if (!(atoi_strict(info[1], &object->material.checker_height) && 1 <= object->material.checker_height))
		return (ERR_MISCONFIGURED_CHECKER);
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

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->material.flag & (1 << MFLAG_BUMPMAP))
		return (ERR_DUPLICATE_MATERIAL);
	object->material.flag |= (1 << MFLAG_BUMPMAP);

	bm = x_malloc(sizeof(t_bumpmap));
	object->image = (t_img *)bm;
	bm->super.image = NULL;
	bm->super.buffer = NULL;
	bm->super.image = mlx_xpm_file_to_image(p->mlx, info[0], &bm->super.width, &bm->super.height);
	if (!bm->super.image)
		return (ERR_MISCONFIGURED_BUMPMAP);
	bm->super.buffer = mlx_get_data_addr(bm->super.image,
										 &bm->super.bits_per_pixel, &bm->super.size_line, &bm->super.endian);
	if (!bm->super.buffer)
		return (ERR_MISCONFIGURED_BUMPMAP);

	if (!(atoi_strict(info[1], &bm->freq_u) && 1 <= bm->freq_u))
		return (ERR_MISCONFIGURED_BUMPMAP);
	if (!(atoi_strict(info[2], &bm->freq_v) && 1 <= bm->freq_v))
		return (ERR_MISCONFIGURED_BUMPMAP);

	return (NO_ERR);
}
