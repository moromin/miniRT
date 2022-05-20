#include <math.h>
#include "../include/miniRT.h"
#include "../include/color.h"
#include "../include/obj_info.h"

t_color ch_pattern_at(const t_obj_info *info, t_uv uv)
{
	const double	uu = uv.u * info->ch_freq_u;
	const double	vv = uv.v * info->ch_freq_v;

	if ((int)(floor(uu) + floor(vv)) % 2 == 0)
		return info->ch_col1;
	else
		return info->ch_col2;
}

t_color	tx_color_at(const t_obj_info *info, t_uv uv)
{
	const double	x = fmod(uv.u * info->tx_freq_u, 1.0) * info->tx_image.width;
	const double	y = fmod(uv.v * info->tx_freq_v, 1.0) * info->tx_image.height;

	return (get_color_from_image(&info->tx_image, (int)x, (int)y));
}
