#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "error.h"

// Error messages
# define ERR_INVALID_ARGS "Invalid number of arguments"
# define ERR_INVALID_FILE "File is invalid (expected '*.rt' file)"
# define ERR_GNL_FAILED "Failed to Get_Next_Line"

void	read_rt_file(int argc, char **argv);

#endif
