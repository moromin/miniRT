#include "../include/scene.h"

static void	check_rt_file(char *filename)
{
	int		fd;
	char	*line;
	int		status;

	fd = x_open(filename, O_RDONLY);
	while (1)
	{
		status = x_get_next_line(fd, &line);
		if (status == GNL_STATUS_DONE)
			break ;
		printf("%s\n", line);
	}
	free(line);

	// TODO: check close() error
	x_close(fd);
}

static bool	check_filename(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension == NULL)
		return (false);
	if (ft_strcmp(extension, ".rt"))
		return (false);
	return (true);
}

void	read_rt_file(int argc, char **argv)
{
	char	*err;

	err = NULL;
	if (argc != 2)
		exit_with_error_message(ERR_INVALID_ARGS);
	if (!check_filename(argv[1]))
		exit_with_error_message(ERR_INVALID_FILE);
	check_rt_file(argv[1]);
}
