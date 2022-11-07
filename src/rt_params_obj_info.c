/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_params_obj_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:22 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:22 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!(atoi_strict(info[0], &object->info.ch_freq_u)
			&& 1 <= object->info.ch_freq_u))
		return (ERR_MISCONFIGURED_CHECKER);
	if (!(atoi_strict(info[1], &object->info.ch_freq_v)
			&& 1 <= object->info.ch_freq_v))
		return (ERR_MISCONFIGURED_CHECKER);
	if (!(get_color_from_str(info[2], &c) && check_color_range(c, 0.0, 255.0)))
		return (ERR_MISCONFIGURED_CHECKER);
	object->info.ch_col1 = color_mult(c, (double)1 / 255);
	if (!(get_color_from_str(info[3], &c) && check_color_range(c, 0.0, 255.0)))
		return (ERR_MISCONFIGURED_CHECKER);
	object->info.ch_col2 = color_mult(c, (double)1 / 255);
	return (NO_ERR);
}

char	*load_bumpmap(t_program *p, char **info)
{
	t_object	*object;
	t_img		*img;

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->info.flag & (1 << FLAG_BUMPMAP))
		return (ERR_DUPLICATE_MATERIAL);
	object->info.flag |= (1 << FLAG_BUMPMAP);
	img = &object->info.bm_image;
	img->image = \
		mlx_xpm_file_to_image(p->mlx, info[0], &img->width, &img->height);
	if (!img->image)
		return (ERR_MISCONFIGURED_BUMPMAP);
	img->buffer = mlx_get_data_addr(img->image,
			 &img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->buffer)
		return (ERR_MISCONFIGURED_BUMPMAP);
	if (!(atoi_strict(info[1], &object->info.bm_freq_u)
			&& 1 <= object->info.bm_freq_u))
		return (ERR_MISCONFIGURED_BUMPMAP);
	if (!(atoi_strict(info[2], &object->info.bm_freq_v)
			&& 1 <= object->info.bm_freq_v))
		return (ERR_MISCONFIGURED_BUMPMAP);
	return (NO_ERR);
}

char	*load_texture(t_program *p, char **info)
{
	t_object	*object;
	t_img		*img;

	if (len(p->objects) == 0)
		return (ERR_UNRESOLVED_MATERIAL);
	object = get_x2(p->objects, -1, 0);
	if (object->info.flag & (1 << FLAG_TEXTURE))
		return (ERR_DUPLICATE_MATERIAL);
	object->info.flag |= (1 << FLAG_TEXTURE);
	img = &object->info.tx_image;
	img->image = \
		mlx_xpm_file_to_image(p->mlx, info[0], &img->width, &img->height);
	if (!img->image)
		return (ERR_MISCONFIGURED_TEXTURE);
	img->buffer = mlx_get_data_addr(img->image,
			 &img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->buffer)
		return (ERR_MISCONFIGURED_TEXTURE);
	if (!(atoi_strict(info[1], &object->info.tx_freq_u)
			&& 1 <= object->info.tx_freq_u))
		return (ERR_MISCONFIGURED_TEXTURE);
	if (!(atoi_strict(info[2], &object->info.tx_freq_v)
			&& 1 <= object->info.tx_freq_v))
		return (ERR_MISCONFIGURED_TEXTURE);
	return (NO_ERR);
}
