#include "../include/scene.h"
#include "../minilibx-linux/mlx.h"

char	*load_checker(t_program *p, char **info)
{
	t_object	*object;
	t_color		c;

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->info.flag & (1 << FLAG_CHECKER))
		return (ERR_DUPLICATE_MATERIAL);
	object->info.flag |= (1 << FLAG_CHECKER);
	if (!(atoi_strict(info[0], &object->info.ch_freq_u) && 1 <= object->info.ch_freq_u))
		return (ERR_MISCONFIGURED_CHECKER);
	if (!(atoi_strict(info[1], &object->info.ch_freq_v) && 1 <= object->info.ch_freq_v))
		return (ERR_MISCONFIGURED_CHECKER);
	if (!(get_color_from_str(info[2], &c) && check_color_range(c, 0.0, 255.0)))
		return (ERR_MISCONFIGURED_CHECKER);
	object->info.ch_col1 = color_mult(c, (double)1/255);
	if (!(get_color_from_str(info[3], &c) && check_color_range(c, 0.0, 255.0)))
		return (ERR_MISCONFIGURED_CHECKER);
	object->info.ch_col2 = color_mult(c, (double)1/255);
	return (NO_ERR);
}

char	*load_bumpmap(t_program *p, char **info)
{
	t_object	*object;
	t_img		*bm_image;

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->info.flag & (1 << FLAG_BUMPMAP))
		return (ERR_DUPLICATE_MATERIAL);
	object->info.flag |= (1 << FLAG_BUMPMAP);
	bm_image = &object->info.bm_image;
	bm_image->image = NULL;
	bm_image->buffer = NULL;
	bm_image->image = mlx_xpm_file_to_image(p->mlx, info[0], &bm_image->width, &bm_image->height);
	if (!bm_image->image)
		return (ERR_MISCONFIGURED_BUMPMAP);
	bm_image->buffer = mlx_get_data_addr(bm_image->image,
										 &bm_image->bits_per_pixel, &bm_image->size_line, &bm_image->endian);
	if (!bm_image->buffer)
		return (ERR_MISCONFIGURED_BUMPMAP);
	if (!(atoi_strict(info[1], &object->info.bm_freq_u) && 1 <= object->info.bm_freq_u))
		return (ERR_MISCONFIGURED_BUMPMAP);
	if (!(atoi_strict(info[2], &object->info.bm_freq_v) && 1 <= object->info.bm_freq_v))
		return (ERR_MISCONFIGURED_BUMPMAP);
	return (NO_ERR);
}
