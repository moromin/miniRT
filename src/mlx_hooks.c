#include "../include/mlx_hooks.h"

#define ESC_KEY 65307

static int	close_window(t_program *p)
{
	delete(p->lights);
	delete_recursively(p->objects, 1);
	mlx_destroy_image(p->mlx, p->img.image);
	mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_display(p->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	key_hook(int code, t_program *p)
{
	if (code == ESC_KEY)
		close_window(p);
	return (0);
}

void	set_mlx_hooks(t_program *p)
{
	mlx_key_hook(p->win, key_hook, p);
	mlx_hook(p->win, 33, 1L << 17, close_window, p);
}