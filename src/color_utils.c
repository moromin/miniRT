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
		free_2d_array((void ***)&rgb);
		return (false);
	}
	is_valid = (ft_strtod(rgb[RED], &c->r)
			&& ft_strtod(rgb[GREEN], &c->g)
			&& ft_strtod(rgb[BLUE], &c->b));
	free_2d_array((void ***)&rgb);
	return (is_valid);
}

bool	check_color_range(t_color c, double min, double max)
{
	const bool	r_ok = (min <= c.r && c.r <= max);
	const bool	g_ok = (min <= c.g && c.g <= max);
	const bool	b_ok = (min <= c.b && c.b <= max);

	return (r_ok && g_ok && b_ok);
}
