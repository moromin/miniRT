/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:23 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 20:02:11 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"
# include "image.h"
# include "vector.h"

typedef struct s_material {
	t_color		k_diffuse;
	t_color		k_specular;
}	t_material;

#endif //MATERIAL_H
