#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*p1;
	const char	*p2;

	if (!dst && !src)
		return (NULL);
	p1 = (char *)dst;
	p2 = (const char *)src;
	while (n-- != 0)
		*p1++ = *p2++;
	return (dst);
}
