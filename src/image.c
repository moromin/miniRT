#include "../include/miniRT.h"
#include "../minilibx-linux/mlx.h"

void	init_image(t_program *program, t_img *img)
{
	img->image = mlx_new_image(program->mlx, WIDTH, HEIGHT);
	img->buffer = mlx_get_data_addr(img->image,
			&img->bits_per_pixel, &img->size_line, &img->endian);
}

void	add_color_to_image(t_img *img, int color, int x, int y)
{
	const int	pixel = (y * img->size_line) + (x * 4);

	img->buffer[pixel + 0] = (char)(color & 0xFF);
	img->buffer[pixel + 1] = (char)((color >> 8) & 0xFF);
	img->buffer[pixel + 2] = (char)((color >> 16) & 0xFF);
	img->buffer[pixel + 3] = (char)(color >> 24);
}
