/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_bbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:40:06 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/16 10:08:45 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_coords	mat4_mul_vec3(const t_matrix *m, const t_coords *point)
{
	t_coords	result;

	result.x = m->matrix[0][0] * point->x + m->matrix[0][1] * point->y + m->matrix[0][2] * point->z + m->matrix[0][3];
	result.y = m->matrix[1][0] * point->x + m->matrix[1][1] * point->y + m->matrix[1][2] * point->z + m->matrix[1][3];
	result.z = m->matrix[2][0] * point->x + m->matrix[2][1] * point->y + m->matrix[2][2] * point->z + m->matrix[2][3];
	return (result);
}

t_aabb	get_bbox_sphere(t_sphere *sphere)
{
	t_aabb	bbox;

	bbox.min.x = sphere->position.x - (sphere->diameter / 2.0);
	bbox.min.y = sphere->position.y - (sphere->diameter / 2.0);
	bbox.min.z = sphere->position.z - (sphere->diameter / 2.0);
	bbox.max.x = sphere->position.x + (sphere->diameter / 2.0);
	bbox.max.y = sphere->position.y + (sphere->diameter / 2.0);
	bbox.max.z = sphere->position.z + (sphere->diameter / 2.0);
	return (bbox);
}

t_aabb	get_bbox_cylinder(t_cylinder *cylinder)
{
	t_aabb	bbox;

	bbox.min.x = cylinder->position.x - (cylinder->diameter / 2.0);
	bbox.min.y = cylinder->position.y - (cylinder->diameter / 2.0);
	bbox.min.z = cylinder->position.z - (cylinder->height / 2.0);
	bbox.max.x = cylinder->position.x + (cylinder->diameter / 2.0);
	bbox.max.y = cylinder->position.y + (cylinder->diameter / 2.0);
	bbox.max.z = cylinder->position.z + (cylinder->height / 2.0);
	return (bbox);
}

t_aabb	get_bbox_plane(t_plane *plane)
{
	t_aabb	bbox;

	bbox.min.x = (plane->position.x - 300.0) * plane->vector.x;
	bbox.min.x = (plane->position.x - 300.0) * plane->vector.y;
	bbox.min.x = (plane->position.x - 300.0) * plane->vector.z;
	bbox.min.x = (plane->position.x + 300.0) * plane->vector.x;
	bbox.min.x = (plane->position.x + 300.0) * plane->vector.y;
	bbox.min.x = (plane->position.x + 300.0) * plane->vector.z;
	return (bbox);
}

t_aabb	get_obj_bbox(t_object *obj)
{
	t_aabb	bbox;
	t_geo_u	geo;

	bbox.min = (t_vec3){FLT_MAX, FLT_MAX, FLT_MAX};
	bbox.max = (t_vec3){FLT_MIN, FLT_MIN, FLT_MIN};
	if (obj->type == SPHERE)
	{
		geo.sphere = (t_sphere *)obj->object;
		geo.sphere->position = mat4_mul_vec3(&geo.sphere->transform, &geo.sphere->position);
		bbox = get_bbox_sphere(geo.sphere);
	}
	else if (obj->type == CYLINDER)
		bbox = get_bbox_cylinder(obj->object);
	else if (obj->type == PLANE)
		bbox = get_bbox_plane(obj->object);
	return (bbox);
}
