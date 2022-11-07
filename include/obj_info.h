/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:24 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:12 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_INFO_H
# define OBJ_INFO_H

# include "../include/image.h"
# include "../include/vector.h"

# define FLAG_CHECKER 0
# define FLAG_BUMPMAP 1
# define FLAG_TEXTURE 2

typedef struct s_obj_info {
	unsigned int	flag;
	t_color			ch_col1;
	t_color			ch_col2;
	int				ch_freq_u;
	int				ch_freq_v;
	t_img			bm_image;
	int				bm_freq_u;
	int				bm_freq_v;
	t_img			tx_image;
	int				tx_freq_u;
	int				tx_freq_v;
}	t_obj_info;

typedef struct s_uv {
	double	u;
	double	v;
}	t_uv;

t_color		ch_color_at(const t_obj_info *info, t_uv uv);
t_color		tx_color_at(const t_obj_info *info, t_uv uv);

t_vector	get_vector_from_normal_map(
				double u, double v, const t_obj_info *info);
t_vector	tangent_to_model(
				t_vector tangent, t_vector t, t_vector b, t_vector n);

#endif
