#include "../include/error.h"

void	exit_with_error_message(const char *msg)
{
    if (errno == 0)
    {
        ft_putstr_fd("ERROR\n", STDERR_FILENO);
        ft_putstr_fd(msg, STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
    }
    else
        perror(msg);
	exit(EXIT_FAILURE);
}
