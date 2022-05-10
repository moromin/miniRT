#include "../include/color.h"
#include "../utils/utils.h"

bool	get_color_from_strs(char **params, t_color *color)
{
	double	val[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!(ft_strtod(params[i], &val[i])
				&& 0.0 <= val[i] && val[i] <= 255.0))
			return (false);
		i++;
	}
	color->r = val[RED];
	color->g = val[GREEN];
	color->b = val[BLUE];
	return (true);
}