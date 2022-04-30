#include "../include/error.h"

void	exit_with_error_message(const char *msg)
{
    ft_putendl_fd("ERROR", STDERR_FILENO);
    if (errno == 0)
        ft_putendl_fd(msg, STDERR_FILENO);
    else
        perror(msg);
	exit(EXIT_FAILURE);
}
