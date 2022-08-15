#include "../include/scene.h"
#include "../include/free.h"
#include "../minilibx-linux/mlx.h"

static const char	*g_env_idents[] = {"A", "C", "L", NULL};
static const char	*g_obj_idents[] = {"sp", "pl", "cy", "co", "sl", "#", "ch", "bm", "tx", NULL};

static char	*check_duplicated_identifier(char *ident, unsigned int *ident_flag)
{
	int			i;

	i = 0;
	while (g_obj_idents[i])
		if (!ft_strcmp(ident, g_obj_idents[i++]))
			return (NO_ERR);
	i = 0;
	while (g_env_idents[i])
		if (!ft_strcmp(ident, g_env_idents[i++]))
			break ;
	if (((*ident_flag >> i) & 1) == 1)
		return (ERR_DUPLICATE_IDENTIFIER);
	*ident_flag |= (1 << i);
	return (NO_ERR);
}

static char	*check_lack_of_identifier(unsigned int ident_flag)
{
	int	i;

	i = 0;
	while (g_env_idents[i++])
		if (((ident_flag >> i) & 1) == 0)
			return (ERR_LACK_IDENTIFIER);
	return (NO_ERR);
}

static char	*load_element(char *line, t_program *p, unsigned int *ident_flag)
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
	else if (num == 6 && !ft_strcmp(info[0], "sl"))
		err = load_spotlight(p, &info[1]);
	else if ((num == 5 || num == 6) && !ft_strcmp(info[0], "co"))
		err = load_cone(p, &info[1]);
	else if (num == 5 && !ft_strcmp(info[0], "ch"))
		err = load_checker(p, &info[1]);
	else if (num == 4 && !ft_strcmp(info[0], "bm"))
		err = load_bumpmap(p, &info[1]);
	else if (num == 4 && !ft_strcmp(info[0], "tx"))
		err = load_texture(p, &info[1]);
	else if (ft_strcmp(info[0], "#"))
		err = ERR_UNDEFINED_IDENTIFIER;
	if (err == NO_ERR)
		err = check_duplicated_identifier(info[0], ident_flag);
	free_2d_array((void ***)&info);
	return (err);
}

static void	read_rt_file(char *filename, t_program *p)
{
	int					fd;
	char				*line;
	int					status;
	char				*err;
	static unsigned int	ident_flag;

	err = NO_ERR;
	fd = x_open(filename, O_RDONLY);
	p->lights = make(sizeof(t_slice *), 0, 1);
	p->objects = make(sizeof(t_slice *), 0, 1);
	while (1)
	{
		status = x_get_next_line(fd, &line);
		if (status == GNL_STATUS_DONE)
			break ;
		if (line[0] != '\0')
			err = load_element(line, p, &ident_flag);
		if (err != NO_ERR)
			break ;
	}
	if (err == NO_ERR)
		err = check_lack_of_identifier(ident_flag);
	free(line);
	x_close(fd);
	if (err != NO_ERR)
	{
		destroy_object_images(p);
		delete_recursively(p->lights, 1);
		delete_recursively(p->objects, 1);
		mlx_destroy_display(p->mlx);
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
