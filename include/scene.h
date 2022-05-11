#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "miniRT.h"
# include "../utils/get_next_line.h"
# include "../utils/utils.h"
# include "../wrapper/x.h"
# include "color.h"
# include "vector.h"
# include "slice.h"

// Element type
# define AMBIENT_LIGHTING 0

// Error messages
# define NO_ERR NULL
# define ERR_INVALID_ARGS "Invalid number of arguments"
# define ERR_INVALID_FILE "File is invalid (expected '*.rt' file)"
# define ERR_INVALID_NUM_OF_ELEMENT_INFO "Invalid number of element information"
# define ERR_MISCONFIGURED_AMBIENT "Ambient lighting is misconfigured"
# define ERR_MISCONFIGURED_CAMERA "Camera is misconfigured"
# define ERR_MISCONFIGURED_LIGHT "Light is misconfigured"
# define ERR_UNDEFINED_IDENTIFIER "Undefined identifier exists"

// scene.c
void	load_rt_file(int argc, char **argv, t_program *program);

// rt_params.c
char	*load_ambient(t_program *p, char **info);
char	*load_camera(t_program *p, char **info);
char	*load_light(t_program *p, char **info);

#endif
