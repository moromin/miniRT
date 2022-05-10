#include "../include/scene.h"

static void	load_rt_parameters(int type, char **info)
{
	char	**params;

	while (*info)
	{
		params = x_split(*info++, ',');
		// TODO: load parameters to t_program
		if (type == AMBIENT_LIGHTING)
		{
			int i = 0;
			double val;
			while (params[i])
			{
				ft_strtod(params[i], &val);
				printf("%lf ", val);
				i++;
			}
		}
		printf("\n");
		free_2d_array((void ***)&params);
	}
}

static void	load_rt_element(char *line)
{
	size_t	num;
	char	**info;

	info = x_split(line, ' ');
	num = count_2d_array((void ***)&info);
	if (num == 3 && !ft_strcmp(info[0], "A"))
		load_rt_parameters(AMBIENT_LIGHTING, ++info);
	else
		printf("%s\n", ERR_INVALID_NUM_OF_ELEMENT_INFO);
	free_2d_array((void ***)&info);
}

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
		load_rt_element(line);
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
