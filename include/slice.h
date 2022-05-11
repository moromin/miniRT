#ifndef SLICE_H
# define SLICE_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "../wrapper/x.h"

typedef struct s_slice {
	void	*org_start;
	void	*cur_start;
	size_t	size;
	size_t	len;
	size_t	cap;
}	t_slice;

t_slice *make(size_t size, size_t len, size_t cap);
void	delete(t_slice *s);
void	append(t_slice *s, void *elem);
void	*get(t_slice *s, size_t index);
size_t	len(t_slice *s);

#endif
