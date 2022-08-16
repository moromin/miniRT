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

// color
# define YELLOW  "\033[33m"      /* Yellow */
# define RESET   "\033[0m"

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
# define ERR_MISCONFIGURED_SPHERE "Sphere is misconfigured"
# define ERR_MISCONFIGURED_PLANE "Plane is misconfigured"
# define ERR_MISCONFIGURED_CYLINDER "Cylinder is misconfigured"
# define ERR_MISCONFIGURED_SPOTLIGHT "Spotlight is misconfigured"
# define ERR_DUPLICATE_IDENTIFIER "Capitalized identifiers are duplicated"
# define ERR_LACK_IDENTIFIER "Capitalized identifiers are lack"
# define ERR_MISCONFIGURED_CONE "Cone is misconfigured"
# define ERR_UNDEFINED_IDENTIFIER "Undefined identifier exists"
# define ERR_UNRESOLVED_MATERIAL "Material is specified before any object"
# define ERR_MISCONFIGURED_CHECKER "Checker is misconfigured"
# define ERR_MISCONFIGURED_BUMPMAP "Bumpmap is misconfigured"
# define ERR_MISCONFIGURED_TEXTURE "Texture is misconfigured"
# define ERR_DUPLICATE_MATERIAL "Material parameter has already been specified"

// Warning messages
# define WARNING_NOT_NORMALIZED "Not normalized vector found, we normalized it!"

# define K_SPECULAR 204

// scene.c
void	load_rt_file(int argc, char **argv, t_program *program);

// read_rt_file.c
char	*read_rt_file(char *filename, t_program *p);

// rt_params.c
char	*load_ambient(t_program *p, char **info);
char	*load_camera(t_program *p, char **info);
char	*load_light(t_program *p, char **info);
char	*load_spotlight(t_program *p, char **info);
char	*load_checker(t_program *p, char **info);
char	*load_bumpmap(t_program *p, char **info);
char	*load_texture(t_program *p, char **info);

// rt_params_obj.c
char	*load_sphere(t_program *p, char **info, size_t param_num);
char	*load_plane(t_program *p, char **info, size_t param_num);
char	*load_cylinder(t_program *p, char **info, size_t param_num);
char	*load_cone(t_program *p, char **info, size_t param_num);

#endif
