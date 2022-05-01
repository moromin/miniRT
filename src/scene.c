#include "../include/scene.h"
#include "../utils/get_next_line.h"
#include "../utils/utils.h"

static char	*check_rt_file(char *filename)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ("open");
	while (1)
	{
		status = get_next_line(fd, &line);
		if (status == GNL_STATUS_DONE)
			break ;
		if (status == GNL_STATUS_ERROR_MALLOC
			|| status == GNL_STATUS_ERROR_READ)
		{
			free(line);
			return (ERR_GNL_FAILED);
		}
	}
	free(line);

	// TODO: check close() error
	close(fd);
	return (NULL);
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
	err = check_rt_file(argv[1]);
	if (err != NULL)
		exit_with_error_message(err);
}
