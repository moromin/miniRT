/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:21 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:21 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.h"
#include "../include/color.h"

#include <stdio.h>

void	vec_print(t_vector v)
{
	printf("X: %f\t", v.x);
	printf("Y: %f\t", v.y);
	printf("Z: %f\n", v.z);
}

void	color_print(t_color c)
{
	printf("R: %f\t", c.r);
	printf("G: %f\t", c.g);
	printf("B: %f\n", c.b);
}
