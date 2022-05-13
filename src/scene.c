#include "../include/scene.h"

static char	*check_capital_identifier(char *ident, bool last)
{
	char const	*envs[] = {"A", "C", "L", NULL};
	char const	*objs[] = {"sp", "pl", "cy", NULL};
	int			i;
	static int	ident_flag;

	i = 0;
	if (last)
	{
		while (envs[i++])
			if (((ident_flag >> i) & 1) == 0)
				return (ERR_LACK_CAPITAL_IDENTIFIER);
		return (NO_ERR);
	}
	while (objs[i])
		if (!ft_strcmp(ident, objs[i++]))
			return (NO_ERR);
	i = 0;
	while (envs[i])
		if (!ft_strcmp(ident, envs[i++]))
			break ;
	if (((ident_flag >> i) & 1) == 1)
		return (ERR_DUPLICATE_CAPITAL_IDENTIFIER);
	ident_flag |= (1 << i);
	return (NO_ERR);
}

static char	*load_element(char *line, t_program *p)
{
	size_t	num;
	char	**info;
	char	*err;

	err = NO_ERR;
	info = x_split(line, ' ');
	num = count_2d_array((void **)info);
	if (num == 3 && !ft_strcmp(info[0], "A"))
		err = load_ambient(p, &info[1]);
	else if (num == 4 && !ft_strcmp(info[0], "C"))
		err = load_camera(p, &info[1]);
	else if (num == 4 && !ft_strcmp(info[0], "L"))
		err = load_light(p, &info[1]);
	else if ((num == 4 || num == 5) && !ft_strcmp(info[0], "sp"))
		err = load_sphere(p, &info[1]);
	else if ((num == 4 || num == 5) && !ft_strcmp(info[0], "pl"))
		err = load_plane(p, &info[1]);
	else if ((num == 6 || num == 7) && !ft_strcmp(info[0], "cy"))
		err = load_cylinder(p, &info[1]);
	else if (ft_strcmp(info[0], "#"))
		err = ERR_UNDEFINED_IDENTIFIER;
	if (err == NO_ERR)
		err = check_capital_identifier(info[0], false);
	free_2d_array((void ***)&info);
	return (err);
}

static void	read_rt_file(char *filename, t_program *p)
{
	int		fd;
	char	*line;
	int		status;
	char	*err;

	err = NO_ERR;
	fd = x_open(filename, O_RDONLY);
	p->lights = make(sizeof(t_light), 0, 1);
	p->objects = make(sizeof(t_slice *), 0, 1);
	while (1)
	{
		status = x_get_next_line(fd, &line);
		if (status == GNL_STATUS_DONE)
			break ;
		if (line[0] != '\0')
			err = load_element(line, p);
		if (err != NO_ERR)
			break ;
	}
	err = check_capital_identifier(NULL, true);
	free(line);
	x_close(fd);
	if (err != NO_ERR)
	{
		delete(p->lights);
		delete_recursively(p->objects, 1);
		exit_with_error_message(err);
	}
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

void	load_rt_file(int argc, char **argv, t_program *p)
{
	if (argc != 2)
		exit_with_error_message(ERR_INVALID_ARGS);
	if (!check_filename(argv[1]))
		exit_with_error_message(ERR_INVALID_FILE);
	read_rt_file(argv[1], p);
}
