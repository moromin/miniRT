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

#endif
