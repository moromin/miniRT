#ifndef RAY_H
# define RAY_H

typedef struct s_ray {
	// 視点位置
	t_vector	start;
	// 視点位置からスクリーン点(x,y)に向かう半直線
	t_vector	direction;
}	t_ray;

#endif
