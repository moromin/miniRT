#include <printf.h>
#include <stdlib.h>
#include <math.h>
#include "../minilibx-linux/mlx.h"
#include "../include/vector.h"
#include "../include/miniRT.h"
#include "../include/scene.h"
#include "../include/math.h"

#define BACKGROUND 0x6495ED
#define OBJECT_NUM 6
#define LIGHT_NUM 3
#define PI 3.141593

void	init_program(t_program *program)
{
	program->mlx = mlx_init();
	program->win = mlx_new_window(program->mlx, WIDTH, HEIGHT, "miniRT");
	init_image(program, &program->img);
	// light setup
	// todo: malloc check, malloc free
	program->lights = malloc(sizeof(t_light) * LIGHT_NUM);
	program->lights[0] = light(vec_init(-5, 5, -5), color(0.5, 0.5, 0.5));
	program->lights[1] = light(vec_init(5, 0, -5), color(0.5, 0.5, 0.5));
	program->lights[2] = light(vec_init(5, 20, -5), color(0.5, 0.5, 0.5));
	// object setup
	// todo: malloc check, malloc free
	program->objects = malloc(sizeof(t_object *) * (OBJECT_NUM + 1));
	program->objects[OBJECT_NUM] = NULL;
	program->objects[0] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->objects[0], 1.0, vec_init(3, 0, 25), color(0.69, 0.0, 0.0), color(0.3, 0.3, 0.3));
	program->objects[1] = (t_object *)malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->objects[1], 1.0, vec_init(2, 0, 20), color(0.0, 0.69, 0.0), color(0.3, 0.3, 0.3));
	program->objects[2] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->objects[2], 1.0, vec_init(1, 0, 15), color(0.0, 0.0, 0.69), color(0.3, 0.3, 0.3));
	program->objects[3] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->objects[3], 1.0, vec_init(0, 0, 10), color(0.0, 0.69, 0.69), color(0.3, 0.3, 0.3));
	program->objects[4] = malloc(sizeof(t_sphere));
	sphere_ctor((t_sphere *)program->objects[4], 1.0, vec_init(-1, 0, 5), color(0.69, 0.0, 0.69), color(0.3, 0.3, 0.3));
	program->objects[5] = (t_object *)malloc(sizeof(t_plane));
	plane_ctor((t_plane *)program->objects[5], vec_init(0, -1, 0), vec_init(0, 1, 0), color(0.69, 0.69, 0.69), color(0.3, 0.3, 0.3));
}

// https://knzw.tech/raytracing/?page_id=1243
t_vector	init_screen_point(t_camera camera, int x, int y)
{
	const t_vector	screen_point = ({
		const double	screen_dist = WIDTH / (2 * tan(PI * camera.fov / 180 / 2));
		const t_vector	df = vec_normalize(vec_sub(camera.normal, camera.pos));
		const t_vector	ey = vec_init(0, 1, 0);
		const t_vector	dx = vec_outer_product(ey, df);
		const t_vector	dy = vec_outer_product(df, dx);
		const t_vector	pm = vec_add(camera.pos, vec_mult(df, screen_dist));
		vec_add(pm, vec_add(
				vec_mult(dx, (2.0 * x) / (WIDTH - 1) - 1.0),
				vec_mult(dy, (-2.0 * y) / (HEIGHT - 1) + 1.0)));
	});

	return (screen_point);
}

int	closest_object(t_object **objects, t_ray ray, double max_dist, bool early_return)
{
	const int	index = ({
			int	res = -1;
			double	min_ray_coefficient = INFINITY;

			for (int i = 0; objects[i]; i++){
				double ray_coefficient = object_solve_ray_equation(objects[i], ray);
				if (ray_coefficient < 0)
					continue;
				t_vector cross_point = vec_add(ray.start, vec_mult(ray.direction, ray_coefficient));
				double dist = vec_magnitude(vec_sub(ray.start, cross_point));
				if (chmin(&min_ray_coefficient, ray_coefficient) && dist <= max_dist)
					res = i;
				if (early_return)
					break;
			}
			res;
	});

	return (index);
}

/*
 * obj_index: 交差している物体
 * cross_point: 視線が物体と最も近く交差している位置ベクトル
 * ray: 交差点から光源への半直線
 * ray.start = 交差点に微小値を足した位置ベクトル
 * ray.direction = 交差点から高原へのベクトル
 * dist = 交差点と光源の距離
 */
t_color	handle_lights(t_program *p, int obj_index, t_vector cross_point)
{
	t_color	c;
	int		i;
	bool	is_covered;
	t_ray	ray;
	double	dist;

	c = p->ambient;
	i = 0;
	while (i < LIGHT_NUM)
	{
		ray.direction = vec_sub(p->lights[i].coordinate, cross_point);
		ray.start = vec_add(cross_point, vec_mult(ray.direction, EPSILON));
		dist = vec_magnitude(ray.direction) - EPSILON;
		is_covered = closest_object(p->objects, ray, dist, true) >= 0;
		if (!is_covered)
			c = color_add(c, object_calc_radiance(p->objects[obj_index], cross_point, p->lights[i]));
		i++;
	}
	return (c);
}

void	draw(t_program *p, int x, int y)
{
	t_vector	screen_point;
	t_ray		ray;
	int			obj_index;
	t_vector	cross_point;
	t_color		color;

	screen_point = init_screen_point(p->camera, x, y);
	ray.start = p->camera.pos;
	ray.direction = vec_sub(screen_point, p->camera.pos);
	obj_index = closest_object(p->objects, ray, INFINITY, false);
	if (obj_index >= 0)
	{
		cross_point = vec_add(ray.start, vec_mult(ray.direction, object_solve_ray_equation(p->objects[obj_index], ray)));
		color = handle_lights(p, obj_index, cross_point);
		color = color_map(color);
		add_color_to_image(&p->img, color_to_int(color), x, y);
	}
	else
		add_color_to_image(&p->img, BACKGROUND, x, y);
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
