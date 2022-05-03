#include "x.h"

void	x_close(int fd)
{
	int	res;

	res = close(fd);
	if (res == -1)
		exit_with_error_message("close");
}
