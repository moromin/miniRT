#include "x.h"

char	**x_split(const char *s, char c)
{
	char	**split;

	split = ft_split(s, c);
	if (!split)
		exit_with_error_message("malloc");
	return (split);
}
