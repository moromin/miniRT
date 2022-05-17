#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"
# include "image.h"

# define MFLAG_CHECKER 0
# define MFLAG_BUMPMAP 1

typedef struct s_material {
	unsigned int	flag;
	// light related
	t_color		diffuse_reflection_coefficient;
	t_color		specular_reflection_coefficient;
	// checker related
	t_color		checker_col1;
	t_color		checker_col2;
	int			checker_width;
	int			checker_height;
}	t_material;

typedef struct s_uv {
	double u;
	double v;
}	t_uv;

t_color ch_pattern_at(t_material material, double u, double v);

typedef struct s_bumpmap
{
	t_img	super;
	int		freq_u;
	int		freq_v;
	double	height_coefficient;
}	t_bumpmap;


#endif //MATERIAL_H
