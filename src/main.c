#include "../minilibx-linux/mlx.h"
#include "../include/vector.h"
#include "../include/miniRT.h"
#include "../include/object.h"

#define RED 0xFF0000
#define BLUE 0x0000FF

void	init_program(t_program *program)
{
	program->mlx = mlx_init();
	program->win = mlx_new_window(program->mlx, WIDTH, HEIGHT, "miniRT");
}

t_vector	init_camera_point(void)
{
	return (vec_init(0, 0, -5));
}

// https://knzw.tech/raytracing/?page_id=1243
t_vector	init_screen_point(int x, int y)
{
	return (vec_init(
			(2.0 * x) / (WIDTH - 1) - 1.0,
			(-2.0 * y) / (HEIGHT - 1) + 1.0,
			0));
}

// screen_point described as 'pw'
void	create_image(t_img *img, t_object *object, t_vector camera_point)
{
	t_vector	screen_point;
	t_ray		ray;
	double		intersect_point;
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			screen_point = init_screen_point(x, y);
			ray.start = camera_point;
			ray.direction = vec_sub(screen_point, camera_point);
			intersect_point = object_intersect_at(object, ray);
			if (intersect_point >= 0)
				add_color_to_image(img, RED, x, y);
			else
				add_color_to_image(img, BLUE, x, y);
			x++;
		}
		y++;
	}
}

// camera_point described as pe
int	main(void)
{
	t_program	program;
	t_img		img;
	t_vector	camera_point;
	t_sphere	sphere;

	// mlx setup
	init_program(&program);
	init_image(&program, &img);
	// camera setup
	camera_point = init_camera_point();
	// object setup
	sphere_ctor(&sphere, 1.0, vec_init(0, 0, 5));
	// create_image
	create_image(&img, (t_object *)&sphere, camera_point);
	mlx_put_image_to_window(program.mlx, program.win, img.image, 0, 0);
	mlx_loop(program.mlx);
}
