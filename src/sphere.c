#include <math.h>

#include "../include/object.h"
#include "../include/math.h"
#include "../include/utils.h"

#define A 0
#define B 1
#define C 2
#define POSITIVE 0
#define NEGATIVE 1

double		sphere_solve_ray_equation(t_object *me, t_ray ray);
int			sphere_raytrace(t_object *me, t_vector cross_point, t_vector light);

void	sphere_ctor(t_sphere *const me, double radius, t_vector center)
{
	static t_object_vtbl const	vtbl = {
			&sphere_solve_ray_equation,
			&sphere_raytrace
	};

	object_ctor(&me->super, center);
	me->super.vptr = &vtbl;
	me->radius = radius;
}

/*
 * typedef struct s_ray {
 *  // 視点位置
 * 	t_vector start;
 *  // 視点位置からスクリーン点(x,y)に向かう半直線
 *  t_vector direction;
 * }
 * watching_vector = camera_vector + t * watching_direction_vector
 * abs(sphere_vector - sphere_center_vector) ^ 2 = radius ^ 2
 * => watching_vector = sphere_vectorで得と
 * t = (-B +- sqrt(B^2 - 4AC)) / 2A
 * A = magnitude(watching_direction_vector) ^ 2
 * B = 2 * (inner_product(camera_vector, watching_direction_vector)
 * 		- inner_product(watching_direction_vector, sphere_center_vector))
 * C = magnitude(camera_vector) ^ 2 + magnitude(sphere_center_vector) ^ 2
 * 		- 2 * (inner_product(camera_vector, sphere_center_vector)
 */
double	sphere_solve_ray_equation(t_object *const me_, t_ray ray)
{
	const t_sphere	*me = (t_sphere *)me_;
	const double	abc[3] = {
			vec_magnitude_squared(ray.direction),
			2 * (vec_inner_product(ray.start, ray.direction)
				 - vec_inner_product(ray.direction, me->super.center)),
			 vec_magnitude_squared(ray.start)
				+ vec_magnitude_squared(me->super.center)
				- 2 * vec_inner_product(ray.start, me->super.center)
				- pow(me->radius, 2)
	};
	const double	d = pow(abc[B], 2) - 4 * abc[A] * abc[C];
	const double	t[2] = {
			(-1 * abc[B] + sqrt(d)) / (2 * abc[A]),
			(-1 * abc[B] - sqrt(d)) / (2 * abc[A])
	};

	if (d < 0 || (t[POSITIVE] < 0 && t[NEGATIVE] < 0))
		return (-1.0);
	if (t[POSITIVE] < 0)
		return (t[NEGATIVE]);
	else if (t[NEGATIVE] < 0)
		return (t[POSITIVE]);
	else
		return (min(t[POSITIVE], t[NEGATIVE]));
}

// normal: 正規化された物体面の法線ベクトル
// incident_direction: 正規化された入射方向ベクトル
// radiance_diffuse: 拡散反射光の放射輝度
int	sphere_raytrace(t_object *me_, t_vector cross_point, t_vector light_point)
{
	const t_sphere	*me = (t_sphere*)me_;
	t_vector		vec;
	const t_vector	normal = ({
		vec = cross_point;
		vec = vec_sub(vec, me->super.center);
		vec_normalize(vec);
	});
	const t_vector	incident_direction = ({
			vec = light_point;
			vec = vec_sub(vec, cross_point);
			vec_normalize(vec);
	});
	double			radiance_diffuse;

	radiance_diffuse = vec_inner_product(normal, incident_direction);
	radiance_diffuse = max(radiance_diffuse, 0);
	return (rgb_to_int(radiance_diffuse, radiance_diffuse, radiance_diffuse));
}
