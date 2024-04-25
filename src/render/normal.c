/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:57:25 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/25 11:44:39 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	sphere_normal(t_vec3 point, t_sphere *sphere)
{
	t_coords	obj_point;
	t_vec3		obj_normal;
	t_vec3		normal;

	obj_point = matrix_multiply_coords(sphere->inversed_t, point);
	obj_normal = subtract_coords(obj_point, sphere->position);
	normal = matrix_multiply_coords(transpose_matrix(&sphere->transform),
			obj_normal);
	return (normal);
}

t_vec3	plane_normal(t_vec3 point, t_plane *plane)
{
	t_vec3	obj_normal;
	t_vec3	normal;

	(void)point;
	obj_normal = set_vector(0, 1, 0);
	normal = matrix_multiply_vector(transpose_matrix(&plane->transform),
			&obj_normal);
	return (normal);
}

t_vec3	cylinder_normal(t_vec3 point, t_cylinder *cy)
{
	double		distance;
	t_coords	obj_point;
	t_vec3		normal;

	obj_point = matrix_multiply_coords(cy->inversed_t, point);
	distance = obj_point.x * obj_point.x + obj_point.z * obj_point.z;
	if (distance < 1 && obj_point.y >= cy->max - EPSILON)
		normal = set_vector(0, 1, 0);
	else if (distance < 1 && obj_point.y <= cy->min + EPSILON)
		normal = set_vector(0, -1, 0);
	else
		normal = set_vector(obj_point.x, 0, obj_point.z);
	normal = matrix_multiply_vector(cy->transform, &normal);
	return (normal);
}

t_vec3	get_normal(t_object *obj, t_vec3 point)
{
	t_vec3	normal;
	t_geo_u	geo;

	geo = get_geo(obj);
	if (obj->type == SPHERE)
		normal = sphere_normal(point, geo.sphere);
	else if (obj->type == CYLINDER)
		normal = cylinder_normal(point, geo.cylinder);
	else
		normal = plane_normal(point, geo.plane);
	return (normalize_vector(normal));
}
