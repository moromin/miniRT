#include "../include/scene.h"

// TODO: check duplicate capital letters
// static bool	check_duplicate_capital_letter()

static char	*load_element(char *line, t_program *program)
{
	size_t	num;
	char	**info;
	char	*err;

	err = NO_ERR;
	info = x_split(line, ' ');
	num = count_2d_array((void **)info);
	// TODO: handle each element
	if (num == 3 && !ft_strcmp(info[0], "A"))
		err = load_ambient(program, &info[1]);
	else if (num == 4 && !ft_strcmp(info[0], "C"))
		err = load_camera(program, &info[1]);
	free_2d_array((void ***)&info);
	return (err);
}

static void	read_rt_file(char *filename, t_program *program)
{
	int		fd;
	char	*line;
	int		status;
	char	*err;

	err = NO_ERR;
	fd = x_open(filename, O_RDONLY);
	while (1)
	{
		status = x_get_next_line(fd, &line);
		if (status == GNL_STATUS_DONE)
			break ;
		err = load_element(line, program);
		if (err != NO_ERR)
			break ;
	}
	free(line);
	x_close(fd);
	if (err != NO_ERR)
		exit_with_error_message(err);
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

void	load_rt_file(int argc, char **argv, t_program *program)
{
	if (argc != 2)
		exit_with_error_message(ERR_INVALID_ARGS);
	if (!check_filename(argv[1]))
		exit_with_error_message(ERR_INVALID_FILE);
	read_rt_file(argv[1], program);
}
