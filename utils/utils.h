#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>

# include "../libft/libft.h"

char	*strappend(char *dst, const char *src, size_t l);
void	exit_with_error_message(const char *msg);
bool	ft_strtod(const char *s, double *val);
size_t	count_2d_array(void ***array);
void	free_2d_array(void ***array);

#endif
