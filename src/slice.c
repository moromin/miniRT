#include "../include/slice.h"

struct s_slice {
	void	*org_start;
	void	*cur_start;
	size_t	size;
	size_t	len;
	size_t	cap;
};

t_slice	*make(size_t size, size_t len, size_t cap)
{
	t_slice	*s;

	if (len > cap)
		assert(0);
	s = x_malloc(sizeof(t_slice));
	s->org_start = x_malloc(size * cap);
	s->cur_start = s->org_start;
	s->size = size;
	s->len = len;
	s->cap = cap;
	ft_bzero(s->org_start, size * len);
	return (s);
}

void	delete(t_slice *s)
{
	free(s->org_start);
	free(s);
}

void	append(t_slice *s, void *elem)
{
	t_slice	*new;

	if (s->len < s->cap)
	{
		ft_memcpy(s->org_start + s->len * s->size, elem, s->size);
		s->len++;
	}
	else
	{
		new = x_malloc(s->size * s->cap * 2);
		ft_memcpy(new, s->cur_start, s->size * s->len);
		free(s->org_start);
		s->cap *= 2;
		s->org_start = new;
		s->cur_start = new;
		append(s, elem);
	}
}

void	*get(t_slice *s, int index)
{
	size_t	i;

	i = index;
	if (index < 0)
		i = index + s->len;
	if (i >= s->len)
		assert(0);
	return (s->cur_start + s->size * i);
}

size_t	len(t_slice *s)
{
	return (s->len);
}
