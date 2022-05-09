#include "../include/color.h"

int	color_to_int(t_color color)
{
	int	rtn;

	rtn = 0;
	rtn |= (int)(color.b * 255);
	rtn |= (int)(color.g * 255) << 8;
	rtn |= (int)(color.r * 255) << 16;
	return (rtn);
}

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
	t_color rtn;

	rtn.r = c1.r * c2.r;
	rtn.g = c1.g * c2.g;
	rtn.b = c1.b * c2.b;
	return (rtn);
}
