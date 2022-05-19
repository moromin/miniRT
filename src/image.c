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

t_color	get_color_from_image(const t_img *img, int x, int y)
{
	const int			pixel = (y * img->size_line) + (x * 4);
	const char			*dst = &img->buffer[pixel];
	const unsigned int	color = *(unsigned int *)dst;
	t_color				c;

	c.b = (double)(color & 0xFF) / 255;
	c.g = (double)((color >> 8) & 0xFF) / 255;
	c.r = (double)((color >> 16) & 0xFF) / 255;
	return (c);
}
