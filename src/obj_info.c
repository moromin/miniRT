#include <math.h>
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
