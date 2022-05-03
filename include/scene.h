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

// Error messages
# define ERR_INVALID_ARGS "Invalid number of arguments"
# define ERR_INVALID_FILE "File is invalid (expected '*.rt' file)"

void	read_rt_file(int argc, char **argv);

#endif
