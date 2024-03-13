/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_bbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:40:06 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/13 14:51:08 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_aabb	get_bbox_sphere(t_sphere *sphere)
{
	t_aabb	bbox;
	double	radius;

	radius = sphere->diameter / 2.0;
	bbox.min.x = sphere->position.x - radius;
	bbox.min.y = sphere->position.y - radius;
	bbox.min.z = sphere->position.z - radius;
	bbox.max.x = sphere->position.x + radius;
	bbox.max.y = sphere->position.y + radius;
	bbox.max.z = sphere->position.z + radius;
	return (bbox);
}

t_aabb	get_bbox_cylinder(t_cylinder *cylinder)
{
	t_aabb	bbox;
	double	radius;
	double	half;

	radius = cylinder->diameter / 2.0;
	half = cylinder->height / 2.0;
	bbox.min.x = cylinder->position.x - radius;
	bbox.min.y = cylinder->position.y - radius;
	bbox.min.z = cylinder->position.z - half;
	bbox.max.x = cylinder->position.x + radius;
	bbox.max.y = cylinder->position.y + radius;
	bbox.max.z = cylinder->position.z + half;
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

	bbox.min.x = bbox.min.y = bbox.min.z = FLT_MAX;
	bbox.max.x = bbox.max.y = bbox.max.z = FLT_MIN;
	if (obj->type == SPHERE)
		bbox = get_bbox_sphere(obj->object);
	else if (obj->type == CYLINDER)
		bbox = get_bbox_cylinder(obj->object);
	else if (obj->type == PLANE)
		bbox = get_bbox_plane(obj->object);
	return (bbox);
}
