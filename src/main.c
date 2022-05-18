#include <printf.h>
#include <stdlib.h>
#include <math.h>
#include "../minilibx-linux/mlx.h"
#include "../include/vector.h"
#include "../include/miniRT.h"
#include "../include/scene.h"
#include "../include/math.h"
#include "../include/mlx_hooks.h"

#define BACKGROUND 0x6495ED

void	init_program(t_program *program)
{
	// program->mlx = mlx_init();
	program->win = mlx_new_window(program->mlx, WIDTH, HEIGHT, "miniRT");
	init_image(program, &program->img);
}

// https://knzw.tech/raytracing/?page_id=1243
t_vector	init_screen_point(t_camera camera, int x, int y)
{
	const t_vector	screen_point = ({
		const double	screen_dist = SCREEN_WIDTH / (2 * tan(M_PI * camera.fov / 180 / 2));
		const t_vector	df = camera.normal;
		const t_vector	ey = vec_init(0, 1, 0);
		t_vector	dx = vec_cross(ey, df);
		if (vec_magnitude(dx) == 0)
			dx = vec_init(1, 0, 0);
		const t_vector	dy = vec_cross(df, dx);
		const t_vector	pm = vec_add(camera.pos, vec_mult(df, screen_dist));
		vec_add(pm, vec_add(
				vec_mult(dx, (2.0 * x) / (WIDTH - 1) - 1.0),
				vec_mult(dy, (-2.0 * y) / (HEIGHT - 1) + 1.0)));
	});

	return (screen_point);
}

int	closest_object(t_slice *objects, t_ray ray, double max_dist, bool early_return)
{
	const int	index = ({
			int	res = -1;
			double	min_ray_coefficient = INFINITY;

			for (int i = 0; i < (int)len(objects); i++){
				double ray_coefficient = object_solve_ray_equation(get_x2(objects, i, 0), ray);
				if (ray_coefficient < 0)
					continue;
				t_vector cross_point = vec_add(ray.start, vec_mult(ray.direction, ray_coefficient));
				double dist = vec_magnitude(vec_sub(ray.start, cross_point));
				if (chmin(&min_ray_coefficient, ray_coefficient) && dist <= max_dist)
				{
					res = i;
					if (early_return)
						break;
				}
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
	size_t	i;
	bool	is_covered;
	t_ray	ray;
	double	dist;

	c = p->ambient;
	i = 0;
	while (i < len(p->lights))
	{
		ray.direction = vec_sub(((t_light *)get_x2(p->lights, i, 0))->pos, cross_point);
		ray.start = vec_add(cross_point, vec_mult(ray.direction, EPSILON));
		dist = vec_magnitude(ray.direction) - EPSILON;
		is_covered = closest_object(p->objects, ray, dist, true) >= 0;
		t_vector camera2cross = vec_sub(cross_point, p->camera.pos);
		if (!is_covered && light_is_reachable(get_x2(p->lights, i, 0), ray.direction))
			c = color_add(c, object_calc_radiance(get_x2(p->objects, obj_index, 0), cross_point, *(t_light *)get_x2(p->lights, i, 0), camera2cross));
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
	ray.direction = vec_sub(screen_point, p->camera.pos);
	ray.start = vec_add(p->camera.pos, vec_mult(ray.direction, EPSILON));
	obj_index = closest_object(p->objects, ray, INFINITY, false);
	if (obj_index >= 0)
	{
		cross_point = vec_add(ray.start, vec_mult(ray.direction, object_solve_ray_equation(get_x2(p->objects, obj_index, 0), ray)));
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

	// To read xpm file
	program.mlx = mlx_init();

	load_rt_file(argc, argv, &program);
	// mlx setup
	init_program(&program);
	// create_image
	create_image(&program);
	printf("--creation of image is done!--\n");
	// mlx setup
	mlx_put_image_to_window(program.mlx, program.win, program.img.image, 0, 0);
	set_mlx_hooks(&program);
	mlx_loop(program.mlx);
}
