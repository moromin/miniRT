#include "../minilibx-linux/mlx.h"
#include "../include/miniRT.h"
#include "../include/scene.h"

int rgb_to_int(double r, double g, double b)
{
	int color = 0;
	color |= (int)(b * 255);
	color |= (int)(g * 255) << 8;
	color |= (int)(r * 255) << 16;
	return (color);
}

void draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color) {
	double	deltaX;
	double	deltaY;
	int 	pixels;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = (int)sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while(pixels)
	{
		mlx_pixel_put(mlx, win, (int)pixelX, (int)pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
}

void print_img(t_program param,void *image, int width, int height, int color) {
	int bits_per_pixel; //32
	int size_line;
	int endian; // 0
	char *buffer = mlx_get_data_addr(image, &bits_per_pixel, &size_line, &endian);

	if (bits_per_pixel != 32)
		color = mlx_get_color_value(param.mlx, color);

	for (int y = 0; y < height; y++) {
//		double grad_color = color;

		for (int x = 0; x < width; x++) {
			// gradation
			double per_x = (double)x / (width - 1); // 0->1
			double per_y = (double)y / (height - 1);
			double grad_color = rgb_to_int(1 - per_x, per_y, (per_x + per_y) / 2);
//			printf("%d: %f\n", x, per);

			int pixel = (y * size_line) + (x * 4);

			if (endian == 1) {
				buffer[pixel + 0] = (char)((int)grad_color >> 24);
				buffer[pixel + 1] = (char)(((int)grad_color >> 16) & 0xFF);
				buffer[pixel + 2] = (char)(((int)grad_color >> 8) & 0xFF);
				buffer[pixel + 3] = (char)((int)grad_color & 0xFF);
			} else if (endian == 0) {
				buffer[pixel + 0] = (char)((int)grad_color & 0xFF);
				buffer[pixel + 1] = (char)(((int)grad_color >> 8) & 0xFF);
				buffer[pixel + 2] = (char)(((int)grad_color >> 16) & 0xFF);
				buffer[pixel + 3] = (char)((int)grad_color >> 24);
			}
		}
	}
}

int main(int argc, char **argv)
{
	// check scene file
	read_rt_file(argc, argv);

	// param setup
	t_program param;
	param.mlx = mlx_init();
	param.win = mlx_new_window(param.mlx, 512, 512, "miniRT Window - Draw Pixel");

	// image setup
	void *image = mlx_new_image(param.mlx, 512, 512);
	int bits_per_pixel; //32
	int size_line;
	int endian; // 0
	char *buffer = mlx_get_data_addr(image, &bits_per_pixel, &size_line, &endian);

	// watching point setup
	t_vector pe;
	pe.dim = 3;
	if (!(pe.comp = malloc(sizeof(double) * 3)))
		return 1;
	pe.comp[0] = 0;
	pe.comp[1] = 0;
	pe.comp[2] = -5;

	// sphere setup
	double r = 1.0;
	t_vector pc;
	pc.dim = 3;
	if (!(pc.comp = malloc(sizeof(double) * 3)))
		return 1;
	pc.comp[0] = 0;
	pc.comp[1] = 0;
	pc.comp[2] = 5;

	// create image
	int width = 512;
	int height = 512;
	for (int y = 0; y < height; y++) {
//		double grad_color = color;

		for (int x = 0; x < width; x++) {
			// screen point in pixel setup
			int pixel = (y * size_line) + (x * 4);

			// screen point in vector setup
			t_vector pw;
			pw.dim = 3;
			if (!(pw.comp = malloc(sizeof(double) * 3)))
				return 1;
			pw.comp[0] = (2.0 * x) / (width - 1) - 1.0;
			pw.comp[1] = (-2.0 * y) / (height - 1) + 1.0;
			pw.comp[2] = 0;

			// math setup
			double a = vec_mag_sq(*vec_sub(pw, pe));
			double b = 2 * (vec_in_pro(pe, *vec_sub(pw, pe)) - vec_in_pro(*vec_sub(pw, pe), pc));
			double c = vec_mag_sq(pe) + vec_mag_sq(pc) - 2 * vec_in_pro(pe, pc) - pow(r, 2);
			// test condition
			double d = pow(b, 2) - 4 * a * c;
			// t pos / neg - I dont think I have to do both
			double t_p = (-1 * b + d) / 2 * a;
			double t_n = (-1 * b - d) / 2 * a;

			// math
			int color;
			// todo: why is there no need to check the value of t
			if (d >= 0 && (t_p >= 0 || t_n >= 0)) {
				// it crosses
				color = 0xFF0000;
			} else {
				// it doesnt cross
				color = 0x0000FF;
			}

			// coloring
			buffer[pixel + 0] = (char)(color & 0xFF);
			buffer[pixel + 1] = (char)((color >> 8) & 0xFF);
			buffer[pixel + 2] = (char)((color >> 16) & 0xFF);
			buffer[pixel + 3] = (char)(color >> 24);

		}
	}

	// looping
	mlx_put_image_to_window(param.mlx, param.win, image, 0, 0);
	mlx_loop(param.mlx);

	return 0;
}
