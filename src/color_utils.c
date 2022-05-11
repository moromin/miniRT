#include "../include/color.h"
#include "../utils/utils.h"
#include "../include/math.h"
#include "../wrapper/x.h"

bool	get_color_from_str(char *params, t_color *c)
{
	char	**rgb;
	bool	is_valid;

	rgb = x_split(params, ',');
	if (count_2d_array((void **)rgb) != 3)
	{
		free_2d_array((void **)rgb);
		return (false);
	}
	is_valid = (ft_strtod(rgb[RED], &c->r)
			&& ft_strtod(rgb[GREEN], &c->g)
			&& ft_strtod(rgb[BLUE], &c->b));
	free_2d_array((void **)rgb);
	return (is_valid);
}

t_color	color_map(t_color c)
{
	c.r = min(1, c.r);
	c.g = min(1, c.g);
	c.b = min(1, c.b);
	return (c);
}
