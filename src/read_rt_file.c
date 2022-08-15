#include "../include/scene.h"
#include "../include/free.h"
#include "../minilibx-linux/mlx.h"

static const char	*g_env_idents[] = {"A", "C", "L", NULL};
static const char	*g_obj_idents[] =
	{"sp", "pl", "cy", "co", "sl", "#", "ch", "bm", "tx", NULL};

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

static char	*classify_element(size_t num, char **info, t_program *p)
{
	if (num == 3 && !ft_strcmp(info[0], "A"))
		return (load_ambient(p, &info[1]));
	else if (num == 4 && !ft_strcmp(info[0], "C"))
		return (load_camera(p, &info[1]));
	else if (num == 4 && !ft_strcmp(info[0], "L"))
		return (load_light(p, &info[1]));
	else if ((num == 4 || num == 5) && !ft_strcmp(info[0], "sp"))
		return (load_sphere(p, &info[1]));
	else if ((num == 4 || num == 5) && !ft_strcmp(info[0], "pl"))
		return (load_plane(p, &info[1]));
	else if ((num == 6 || num == 7) && !ft_strcmp(info[0], "cy"))
		return (load_cylinder(p, &info[1]));
	else if (num == 6 && !ft_strcmp(info[0], "sl"))
		return (load_spotlight(p, &info[1]));
	else if ((num == 5 || num == 6) && !ft_strcmp(info[0], "co"))
		return (load_cone(p, &info[1]));
	else if (num == 5 && !ft_strcmp(info[0], "ch"))
		return (load_checker(p, &info[1]));
	else if (num == 4 && !ft_strcmp(info[0], "bm"))
		return (load_bumpmap(p, &info[1]));
	else if (num == 4 && !ft_strcmp(info[0], "tx"))
		return (load_texture(p, &info[1]));
	else if (ft_strcmp(info[0], "#"))
		return (ERR_UNDEFINED_IDENTIFIER);
	return (NO_ERR);
}

static char	*load_element(char *line, t_program *p, unsigned int *ident_flag)
{
	size_t	num;
	char	**info;
	char	*err;

	info = x_split(line, ' ');
	num = count_2d_array((void **)info);
	err = classify_element(num, info, p);
	if (err == NO_ERR)
		err = check_duplicated_identifier(info[0], ident_flag);
	free_2d_array((void ***)&info);
	return (err);
}

char	*read_rt_file(char *filename, t_program *p)
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
	return (err);
}
