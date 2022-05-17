#include "../include/mlx_hooks.h"
#include "../include/free.h"

#define ESC_KEY 65307

static int	close_window(t_program *p)
{
	destroy_object_images(p);
	delete_recursively(p->lights, 1);
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
