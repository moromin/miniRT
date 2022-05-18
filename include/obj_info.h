#ifndef OBJ_INFO_H
# define OBJ_INFO_H

# include "../include/image.h"
# include "../include/vector.h"

# define FLAG_CHECKER 0
# define FLAG_BUMPMAP 1

typedef struct s_obj_info {
	unsigned int	flag;
	// checker related
	t_color		ch_col1;
	t_color		ch_col2;
	int			ch_freq_u;
	int			ch_freq_v;
	// bumpmap related
	t_img		*bm_image;
	int			bm_freq_u;
	int			bm_freq_v;
}	t_obj_info;

typedef struct s_uv {
	double u;
	double v;
}	t_uv;

t_color ch_pattern_at(const t_obj_info *info, t_uv uv);

//t_vector	get_vector_from_normal_map(double u, double v, t_bumpmap bm);
//t_vector	tangent_to_model(t_vector tangent, t_vector t, t_vector b, t_vector n);

#endif