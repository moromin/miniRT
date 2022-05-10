#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../utils/get_next_line.h"
# include "../utils/utils.h"
# include "../wrapper/x.h"

// Element type
# define AMBIENT_LIGHTING 0

// Error messages
# define ERR_INVALID_ARGS "Invalid number of arguments"
# define ERR_INVALID_FILE "File is invalid (expected '*.rt' file)"
# define ERR_INVALID_NUM_OF_ELEMENT_INFO "Invalid number of element information"

// scene.c
void	read_rt_file(int argc, char **argv);

#endif
