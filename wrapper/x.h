#ifndef X_H
# define X_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../utils/utils.h"

int		x_open(const char *path, int mode);
void	x_close(int fd);
int		x_get_next_line(int fd, char **line);
char	**x_split(const char *s, char c);
void	*x_malloc(size_t size);

#endif
