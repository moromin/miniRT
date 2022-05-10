#include <printf.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"
#include "../include/vector.h"
#include "../include/miniRT.h"
#include "../include/light.h"
#include "../include/scene.h"

#define BACKGROUND 0x6495ED
#define OBJECT_NUM 1

void	init_program(t_program *program)
{
	program->mlx = mlx_init();
	program->win = mlx_new_window(program->mlx, WIDTH, HEIGHT, "miniRT");
	init_image(program, &program->img);
	// camera setup
	program->camera_point = vec_init(0, 0, -5);
	// light setup
	program->light = light(vec_init(-5, 5, -5), color(1.0, 1.0, 1.0));
	// object setup
	// todo: malloc check, malloc free
	program->object = malloc(sizeof(t_object *) * OBJECT_NUM);
	program->object[0] = (t_object *)malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->object[0], 1.0, vec_init(0, 0, 5), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
}

// https://knzw.tech/raytracing/?page_id=1243
t_vector	init_screen_point(int x, int y)
{
	return (vec_init(
			(2.0 * x) / (WIDTH - 1) - 1.0,
			(-2.0 * y) / (HEIGHT - 1) + 1.0,
			0));
}

void	draw(t_program *program, int x, int y)
{
	t_vector	screen_point;
	t_ray		ray;
	double		ray_coefficient;
	t_vector	cross_point;
	t_color		color;

	screen_point = init_screen_point(x, y);
	ray.start = program->camera_point;
	ray.direction = vec_sub(screen_point, program->camera_point);
	ray_coefficient = object_solve_ray_equation(program->object[0], ray);
	if (ray_coefficient >= 0)
	{
		cross_point = vec_add(ray.start,
				  vec_mult(ray.direction, ray_coefficient));
		color = object_calc_radiance(program->object[0], cross_point, program->light, program->ambient);
		add_color_to_image(&program->img, color_to_int(color), x, y);
	}
	else
		add_color_to_image(&program->img, BACKGROUND, x, y);
}

// screen_point described as 'pw'
void	create_image(t_program *program)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			draw(program, x, y);
			x++;
		}
		y++;
	}
}

// camera_point described as pe
int	main(int argc, char **argv)
{
	t_program	program;

	load_rt_file(argc, argv, &program);
	// mlx setup
	init_program(&program);
	// create_image
	create_image(&program);
	// mlx setup
	mlx_put_image_to_window(program.mlx, program.win, program.img.image, 0, 0);
	mlx_loop(program.mlx);
	return (EXIT_SUCCESS);
}
