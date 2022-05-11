#include "x.h"

void	*x_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		exit_with_error_message("malloc");
	return (res);
}
