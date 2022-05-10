#include <printf.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"
#include "../include/vector.h"
#include "../include/miniRT.h"
#include "../include/light.h"
#include "../include/scene.h"
#include "../include/math.h"

#define BACKGROUND 0x6495ED
#define OBJECT_NUM 6

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
	program->object = malloc(sizeof(t_object *) * (OBJECT_NUM + 1));
	program->object[OBJECT_NUM] = NULL;
	program->object[0] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->object[0], 1.0, vec_init(3, 0, 25), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
	program->object[1] = (t_object *)malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->object[1], 1.0, vec_init(2, 0, 20), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
	program->object[2] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->object[2], 1.0, vec_init(1, 0, 15), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
	program->object[3] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->object[3], 1.0, vec_init(0, 0, 10), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
	program->object[4] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->object[4], 1.0, vec_init(-1, 0, 5), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
	program->object[5] = (t_object *)malloc(sizeof(t_plane));
	plane_ctor((t_plane *)program->object[5], vec_init(0, -1, 0), vec_init(0, 1, 0), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
}

// https://knzw.tech/raytracing/?page_id=1243
t_vector	init_screen_point(int x, int y)
{
	return (vec_init(
			(2.0 * x) / (WIDTH - 1) - 1.0,
			(-2.0 * y) / (HEIGHT - 1) + 1.0,
			0));
}

int	closest_object(t_object **objects, t_ray ray)
{
	const int	index = ({
			int	res = -1;
			double ray_coefficient;
			double	min_ray_coefficient = INFINITY;

			for (int i = 0; objects[i]; i++){
				ray_coefficient = object_solve_ray_equation(objects[i], ray);
				if (ray_coefficient < 0)
					continue;
				if (chmin(&min_ray_coefficient, ray_coefficient))
					res = i;
			}
			res;
	});

	return (index);
}

void	draw(t_program *program, int x, int y)
{
	t_vector	screen_point;
	t_ray		ray;
	int			obj_index;
	t_vector	cross_point;
	t_color		color;

	screen_point = init_screen_point(x, y);
	ray.start = program->camera_point;
	ray.direction = vec_sub(screen_point, program->camera_point);
	obj_index = closest_object(program->object, ray);
	if (obj_index >= 0)
	{
		cross_point = vec_add(ray.start, vec_mult(ray.direction, object_solve_ray_equation(program->object[obj_index], ray)));
		color = object_calc_radiance(program->object[obj_index], cross_point, program->light, program->ambient);
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
