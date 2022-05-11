#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

typedef struct s_camera
{
	t_vector	pos;
	t_vector	normal;
	double		fov;
}	t_camera;

#endif
