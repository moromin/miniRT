#include "../include/free.h"
#include "../minilibx-linux/mlx.h"

void	destroy_object_images(t_program *p)
{
	int			i;
	t_object	*object;
	t_bumpmap	*bm;

	i = 0;
	while (i < (int)len(p->objects))
	{
		object = get_x2(p->objects, i, 0);
		if (object->info.flag & 1 << FLAG_BUMPMAP)
		{
			bm = (t_bumpmap *)object->image;
			if (bm->super.image)
				mlx_destroy_image(p->mlx, bm->super.image);
			free(bm);
			bm = NULL;
		}
		i++;
	}
}
