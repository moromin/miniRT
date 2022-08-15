#include "../include/scene.h"

char	*load_sphere(t_program *p, char **info)
{
	const t_slice	*sphere = ({
		const t_slice	*sp = make(sizeof(t_sphere), 1, 1);
		t_vector		center;
		double			radius;
		t_color			k_diffuse;
		t_color			k_specular;

		if (!get_vector_from_str(info[0], &center))
			return (ERR_MISCONFIGURED_SPHERE);
		if (!ft_strtod(info[1], &radius))
			return (ERR_MISCONFIGURED_SPHERE);
		radius /= 2;
		if (!(get_color_from_str(info[2], &k_diffuse)
				&& check_color_range(k_diffuse, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_SPHERE);
		k_specular = color(DEF_K_SPECULAR, DEF_K_SPECULAR, DEF_K_SPECULAR);
		if (count_2d_array((void **)info) == 4
			&& !(get_color_from_str(info[3], &k_specular)
				&& check_color_range(k_specular, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_SPHERE);
		t_sphere_attrs attrs = {radius, center,color_mult(k_diffuse, (double)1 / 255),color_mult(k_specular, (double)1 / 255)};
		sphere_ctor(get(sp, 0), &attrs);
		sp;
	});

	append(p->objects, &sphere);
	return (NO_ERR);
}

char	*load_plane(t_program *p, char **info)
{
	const t_slice	*plane = ({
		const t_slice	*pl = make(sizeof(t_plane), 1, 1);
		t_vector		center;
		t_vector		normal;
		t_color			k_diffuse;
		t_color			k_specular;

		if (!get_vector_from_str(info[0], &center))
			return (ERR_MISCONFIGURED_PLANE);
		if (!(get_vector_from_str(info[1], &normal)
			  && check_vector_range(normal, -1.0, 1.0)))
			return (ERR_MISCONFIGURED_PLANE);
		if (vec_magnitude_squared(normal) != 1)
		{
			ft_putendl_fd(WARNING_NOT_NORMALIZED, STDERR_FILENO);
			normal = vec_normalize(normal);
		}
		if (!(get_color_from_str(info[2], &k_diffuse)
			  && check_color_range(k_diffuse, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_PLANE);
		k_specular = color(DEF_K_SPECULAR, DEF_K_SPECULAR, DEF_K_SPECULAR);
		if (count_2d_array((void **)info) == 4
			&& !(get_color_from_str(info[3], &k_specular)
				 && check_color_range(k_specular, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_PLANE);
		t_plane_attrs attrs = {center, normal,color_mult(k_diffuse, (double)1 / 255),color_mult(k_specular, (double)1 / 255)};
		plane_ctor(get(pl, 0), &attrs);
		pl;
	});

	append(p->objects, &plane);
	return (NO_ERR);
}

char	*load_cylinder(t_program *p, char **info)
{
	const t_slice		*cylinder = ({
		t_slice		*cy = make(sizeof(t_cylinder), 1, 1);
		t_vector	center;
		t_vector	normal;
		double		radius;
		double		height;
		t_color		k_diffuse;
		t_color		k_specular;

		if (!get_vector_from_str(info[0], &center))
			return (ERR_MISCONFIGURED_CYLINDER);
		if (!(get_vector_from_str(info[1], &normal)
			&& check_vector_range(normal, -1.0, 1.0)))
			return (ERR_MISCONFIGURED_CYLINDER);
		if (vec_magnitude_squared(normal) != 1)
		{
			ft_putendl_fd(WARNING_NOT_NORMALIZED, STDERR_FILENO);
			normal = vec_normalize(normal);
		}
		if (!ft_strtod(info[2], &radius))
			return (ERR_MISCONFIGURED_CYLINDER);
		radius /= 2;
		if (!ft_strtod(info[3], &height))
			return (ERR_MISCONFIGURED_CYLINDER);
		if (!(get_color_from_str(info[4], &k_diffuse)
			&& check_color_range(k_diffuse, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_CYLINDER);
		k_specular = color(DEF_K_SPECULAR, DEF_K_SPECULAR, DEF_K_SPECULAR);
		if (count_2d_array((void **)info) == 6
			&& !(get_color_from_str(info[5], &k_specular)
			&& check_color_range(k_specular, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_CYLINDER);
		cylinder_ctor(get(cy, 0), center, normal, radius, height, color_mult(k_diffuse, (double)1 / 255), color_mult(k_specular, (double)1 / 255));
		cy;
	});

	append(p->objects, &cylinder);
	return (NO_ERR);
}

char	*load_cone(t_program *p, char **info)
{
	const t_slice	*cone = ({
			t_slice		*co = make(sizeof(t_cone), 1, 1);
			t_vector	center;
			t_vector	normal;
			double		aperture;
			t_color		k_diffuse;
			t_color		k_specular;

			if (!get_vector_from_str(info[0], &center))
				return (ERR_MISCONFIGURED_CONE);
			if (!(get_vector_from_str(info[1], &normal)
				&& check_vector_range(normal, -1.0, 1.0)))
				return (ERR_MISCONFIGURED_CONE);
			if (vec_magnitude_squared(normal) != 1)
			{
				ft_putendl_fd(WARNING_NOT_NORMALIZED, STDERR_FILENO);
				normal = vec_normalize(normal);
			}
			if (!(ft_strtod(info[2], &aperture)
				&& 0.0 <= aperture && aperture < 180.0))
				return (ERR_MISCONFIGURED_CONE);
			if (!(get_color_from_str(info[3], &k_diffuse)
				&& check_color_range(k_diffuse, 0.0, 255.0)))
				return (ERR_MISCONFIGURED_CONE);
			k_specular = color(DEF_K_SPECULAR, DEF_K_SPECULAR, DEF_K_SPECULAR);
			if (count_2d_array((void **)info) == 5
				&& !(get_color_from_str(info[4], &k_specular)
				&& check_color_range(k_specular, 0.0, 255.0)))
				return (ERR_MISCONFIGURED_CONE);
			cone_ctor(get(co, 0), center, normal, aperture, color_mult(k_diffuse, (double)1 / 255), color_mult(k_specular, (double)1 / 255));
			co;
	});

	append(p->objects, &cone);
	return (NO_ERR);
}
