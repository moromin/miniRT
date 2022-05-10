#include <stdbool.h>

double	min(double a, double b)
{
	if (a >= b)
		return (b);
	return (a);
}

double	max(double a, double b)
{
	if (a <= b)
		return (b);
	return (a);
}

bool	chmin(double *a, double b)
{
	if (*a > b)
	{
		*a = b;
		return (true);
	}
	return (false);
}
