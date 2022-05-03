#include "x.h"

int	x_open(const char *path, int mode)
{
	int	fd;

	fd = open(path, mode);
	if (fd == -1)
		exit_with_error_message("open");
	return (fd);
}
