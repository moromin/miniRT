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

#endif //MATERIAL_H
