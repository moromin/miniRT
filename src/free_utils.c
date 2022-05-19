#include "../include/free.h"
#include "../minilibx-linux/mlx.h"

void	destroy_object_images(t_program *p)
{
	int			i;
	t_object	*object;

	i = 0;
	while (i < (int)len(p->objects))
	{
		object = get_x2(p->objects, i, 0);
		if (object->info.flag & 1 << FLAG_BUMPMAP)
			if (object->info.bm_image.image)
				mlx_destroy_image(p->mlx, object->info.bm_image.image);
		if (object->info.flag & 1 << FLAG_TEXTURE)
			if (object->info.tx_image.image)
				mlx_destroy_image(p->mlx, object->info.tx_image.image);
		i++;
	}
}
