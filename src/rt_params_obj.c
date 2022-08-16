#include "../include/scene.h"

static t_vector	normalize_object_normal_vector(t_vector normal);

char	*load_sphere(t_program *p, char **info, size_t param_num)
{
	const t_slice	*sphere = ({
		const t_slice	*sp = make(sizeof(t_sphere), 1, 1);
		t_sphere_attrs	attrs;

		attrs.k_specular = color(K_SPECULAR, K_SPECULAR, K_SPECULAR);
		if (!(get_vector_from_str(info[0], &attrs.center)
			&& ft_strtod(info[1], &attrs.radius)
			&& (get_color_from_str(info[2], &attrs.k_diffuse)
				&& check_color_range(attrs.k_diffuse, 0.0, 255.0))))
			return (ERR_MISCONFIGURED_SPHERE);
		if (param_num == 4 && !(get_color_from_str(info[3], &attrs.k_specular)
				&& check_color_range(attrs.k_specular, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_SPHERE);
		attrs.radius /= 2;
		attrs.k_diffuse = color_mult(attrs.k_diffuse, (double)1 / 255);
		attrs.k_specular = color_mult(attrs.k_specular, (double)1 / 255);
		sphere_ctor(get(sp, 0), &attrs);
		sp;
	});

	append(p->objects, &sphere);
	return (NO_ERR);
}

char	*load_plane(t_program *p, char **info, size_t param_num)
{
	const t_slice	*plane = ({
		const t_slice	*pl = make(sizeof(t_plane), 1, 1);
		t_plane_attrs	attrs;

		attrs.k_specular = color(K_SPECULAR, K_SPECULAR, K_SPECULAR);
		if (!(get_vector_from_str(info[0], &attrs.center)
			&& (get_vector_from_str(info[1], &attrs.normal)
				&& check_vector_range(attrs.normal, -1.0, 1.0))
			&& (get_color_from_str(info[2], &attrs.k_diffuse)
				&& check_color_range(attrs.k_diffuse, 0.0, 255.0))))
			return (ERR_MISCONFIGURED_PLANE);
		if (param_num == 4 && !(get_color_from_str(info[3], &attrs.k_specular)
				&& check_color_range(attrs.k_specular, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_PLANE);
		attrs.normal = normalize_object_normal_vector(attrs.normal);
		attrs.k_diffuse = color_mult(attrs.k_diffuse, (double)1 / 255);
		attrs.k_specular = color_mult(attrs.k_specular, (double)1 / 255);
		plane_ctor(get(pl, 0), &attrs);
		pl;
	});

	append(p->objects, &plane);
	return (NO_ERR);
}

char	*load_cylinder(t_program *p, char **info, size_t param_num)
{
	const t_slice		*cylinder = ({
		t_slice				*cy = make(sizeof(t_cylinder), 1, 1);
		t_cylinder_attrs	attrs;
		attrs.k_specular = color(K_SPECULAR, K_SPECULAR, K_SPECULAR);
		if (!(get_vector_from_str(info[0], &attrs.center)
			&& (get_vector_from_str(info[1], &attrs.normal)
				&& check_vector_range(attrs.normal, -1.0, 1.0))
			&& ft_strtod(info[2], &attrs.radius)
			&& ft_strtod(info[3], &attrs.height)
			&& (get_color_from_str(info[4], &attrs.k_diffuse)
				&& check_color_range(attrs.k_diffuse, 0.0, 255.0))))
			return (ERR_MISCONFIGURED_CYLINDER);
		if (param_num == 6 && !(get_color_from_str(info[5], &attrs.k_specular)
			&& check_color_range(attrs.k_specular, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_CYLINDER);
		attrs.radius /= 2;
		attrs.normal = normalize_object_normal_vector(attrs.normal);
		attrs.k_diffuse = color_mult(attrs.k_diffuse, (double)1 / 255);
		attrs.k_specular = color_mult(attrs.k_specular, (double)1 / 255);
		cylinder_ctor(get(cy, 0), &attrs);
		cy;
	});

	append(p->objects, &cylinder);
	return (NO_ERR);
}

char	*load_cone(t_program *p, char **info, size_t param_num)
{
	const t_slice	*cone = ({
		t_slice			*co = make(sizeof(t_cone), 1, 1);
		t_cone_attrs	attrs;

		attrs.k_specular = color(K_SPECULAR, K_SPECULAR, K_SPECULAR);
		if (!(get_vector_from_str(info[0], &attrs.center)
			&& (get_vector_from_str(info[1], &attrs.normal)
				&& check_vector_range(attrs.normal, -1.0, 1.0))
			&& (ft_strtod(info[2], &attrs.aperture)
				&& 0.0 <= attrs.aperture && attrs.aperture < 180.0)
			&& (get_color_from_str(info[3], &attrs.k_diffuse)
				&& check_color_range(attrs.k_diffuse, 0.0, 255.0))))
			return (ERR_MISCONFIGURED_CONE);
		if (param_num == 5 && !(get_color_from_str(info[4], &attrs.k_specular)
			&& check_color_range(attrs.k_specular, 0.0, 255.0)))
			return (ERR_MISCONFIGURED_CONE);
		attrs.normal = normalize_object_normal_vector(attrs.normal);
		attrs.k_diffuse = color_mult(attrs.k_diffuse, (double)1 / 255);
		attrs.k_specular = color_mult(attrs.k_specular, (double)1 / 255);
		cone_ctor(get(co, 0), &attrs);
		co;
	});

	append(p->objects, &cone);
	return (NO_ERR);
}

static t_vector	normalize_object_normal_vector(t_vector normal)
{
	if (vec_magnitude_squared(normal) != 1)
	{
		ft_putendl_fd(YELLOW WARNING_NOT_NORMALIZED RESET, STDERR_FILENO);
		normal = vec_normalize(normal);
	}
	return (normal);
}
