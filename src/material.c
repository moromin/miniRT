#include <math.h>
#include "../include/object.h"

t_color ch_pattern_at(t_material material, double u, double v)
{
	const double	uu = u * material.checker_width;
	const double	vv = v * material.checker_height;

	if ((int)(floor(uu) + floor(vv)) % 2 == 0)
		return material.checker_col1;
	else
		return material.checker_col2;
}
