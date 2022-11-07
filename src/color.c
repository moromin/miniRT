/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumihara <thara@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:57:21 by takumihar         #+#    #+#             */
/*   Updated: 2022/11/07 19:57:21 by takumihar        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/color.h"

t_color	color(double r, double g, double b)
{
	t_color	rtn;

	rtn.r = r;
	rtn.g = g;
	rtn.b = b;
	return (rtn);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	rtn;

	rtn.r = c1.r + c2.r;
	rtn.g = c1.g + c2.g;
	rtn.b = c1.b + c2.b;
	return (rtn);
}

t_color	color_mult(t_color c, double k)
{
	t_color	rtn;

	rtn.r = c.r * k;
	rtn.g = c.g * k;
	rtn.b = c.b * k;
	return (rtn);
}

t_color	color_prod(t_color c1, t_color c2)
{
	t_color	rtn;

	rtn.r = c1.r * c2.r;
	rtn.g = c1.g * c2.g;
	rtn.b = c1.b * c2.b;
	return (rtn);
}
