#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"
# include "image.h"
# include "vector.h"

typedef struct s_material {
	// light related
	t_color		k_diffuse;
	t_color		k_specular;
}	t_material;

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
