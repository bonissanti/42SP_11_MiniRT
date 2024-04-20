/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:57:25 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/20 18:47:35 by rseelaen         ###   ########.fr       */
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
	t_vec3		obj_normal;
	t_vec3		normal;

	(void)point;
	obj_normal = set_vector(0, 1, 0);
	normal = matrix_multiply_vector(transpose_matrix(&plane->transform),
			&obj_normal);
	return (normal);
}

// t_vec3	cylinder_normal(t_vec3 point, t_cylinder *cyl)
// {
// 	t_coords	obj_point;
// 	t_vec3		obj_normal;
// 	t_vec3		normal;
// 	double		dist;

// 	obj_point = matrix_multiply_coords(cyl->inversed_t, point);
// 	dist = pow(obj_point.x, 2) + pow(obj_point.z, 2);
// 	if (dist < 1 && obj_point.y >= cyl->max - EPSILON)
// 		obj_normal = set_vector(0, 1, 0);
// 	else if (dist < 1 && obj_point.y <= cyl->min + EPSILON)
// 		obj_normal = set_vector(0, -1, 0);
// 	else
// 		obj_normal = set_vector(obj_point.x, 0, obj_point.z);
// 	normal = matrix_multiply_vector(transpose_matrix(&cyl->transform),
// 			&obj_normal);
// 	return (normal);
// }

t_vec3	cylinder_normal(t_vec3 *point, t_cylinder *cy)
{
	t_vec3	base;
	t_vec3	base_to_point;
	t_vec3	closest_point_on_axis;
	t_vec3	normal;
	double	projection_length;

	base = (t_vec3){cy->position.x, cy->position.y,
		cy->position.z};
	base_to_point = subtract_tuple(matrix_multiply_coords(cy->inversed_t,
				*point), base);
	// base_to_point = base;
	projection_length = dot_product(base_to_point, cy->vector);
	closest_point_on_axis = add_tuple(cy->position, multiply_tuple(cy->vector,
				projection_length));
	normal = subtract_tuple(*point, closest_point_on_axis);
	normal = matrix_multiply_vector(transpose_matrix(&cy->transform),
			&normal);
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
		normal = cylinder_normal(&point, geo.cylinder);
	else
		normal = plane_normal(point, geo.plane);
	return (normalize_vector(normal));
}
