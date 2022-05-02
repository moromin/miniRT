#include "../utils/get_next_line.h"

int	x_get_next_line(int fd, char **line)
{
	t_gnl_status	status;

	status = get_next_line(fd, line);
	if (status == GNL_STATUS_ERROR_MALLOC)
		exit_with_error_message("malloc");
	if (status == GNL_STATUS_ERROR_READ)
		exit_with_error_message("read");
	return (status);
}
