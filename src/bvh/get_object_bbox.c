/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_bbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:40:06 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/12 12:41:44 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <float.h>	

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
