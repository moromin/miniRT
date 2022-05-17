#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"
# include "image.h"
# include "vector.h"

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

// bumpmap
typedef struct s_bumpmap
{
	t_img	super;
	int		freq_u;
	int		freq_v;
}	t_bumpmap;

t_vector	get_vector_from_normal_map(double u, double v, t_bumpmap bm);
t_vector	tangent_to_model(t_vector tangent, t_vector t, t_vector b, t_vector n);

#endif //MATERIAL_H
