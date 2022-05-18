#include "../include/slice.h"

struct s_slice {
	void	*org_start;
	void	*cur_start;
	size_t	size;
	size_t	len;
	size_t	cap;
};

void	delete_recursively(t_slice *s, int depth)
{
	size_t	i;
	t_slice	*next;

	depth--;
	i = 0;
	while (i < s->len)
	{
		next = (t_slice *)s->org_start + s->size * i;
		if (depth == 0)
			delete(next);
		else
			delete_recursively(next, depth);
		i++;
	}
	delete(s);
}

void	*get_x2(t_slice *s, int i1, int i2)
{
	return (get(*(t_slice **)get(s, i1), i2));
}
