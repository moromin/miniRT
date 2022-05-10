#include "../include/scene.h"

// TODO: check duplicate capital letters
// static bool	check_duplicate_capital_letter()

static void	load_rt_element(char *line, t_program *program)
{
	size_t	num;
	char	**info;

	info = x_split(line, ' ');
	num = count_2d_array((void ***)&info);
	// TODO: handle each element
	if (num == 3 && !ft_strcmp(info[0], "A"))
		load_ambient(program, ++info);
	free_2d_array((void ***)&info);
}

static void	read_rt_file(char *filename, t_program *program)
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
		load_rt_element(line, program);
	}
	free(line);
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

void	load_rt_file(int argc, char **argv, t_program *program)
{
	if (argc != 2)
		exit_with_error_message(ERR_INVALID_ARGS);
	if (!check_filename(argv[1]))
		exit_with_error_message(ERR_INVALID_FILE);
	read_rt_file(argv[1], program);
}
