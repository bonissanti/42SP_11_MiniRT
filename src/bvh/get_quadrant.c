/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quadrant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:43:25 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/12 17:53:28 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	cylinder_quadrant(t_cylinder *cylinder)
{
	if (cylinder->position.x > 0 && cylinder->position.y > 0)
		return (1);
	else if (cylinder->position.x < 0 && cylinder->position.y > 0)
		return (2);
	else if (cylinder->position.x < 0 && cylinder->position.y < 0)
		return (3);
	else if (cylinder->position.x > 0 && cylinder->position.y < 0)
		return (4);
	return (0);
}

static int	plane_quadrant(t_plane *plane)
{
	if (plane->position.x > 0 && plane->position.y > 0)
		return (1);
	else if (plane->position.x < 0 && plane->position.y > 0)
		return (2);
	else if (plane->position.x < 0 && plane->position.y < 0)
		return (3);
	else if (plane->position.x > 0 && plane->position.y < 0)
		return (4);
	return (0);
}

static int	sphere_quadrant(t_sphere *sphere)
{
	if (sphere->position.x > 0 && sphere->position.y > 0)
		return (1);
	else if (sphere->position.x < 0 && sphere->position.y > 0)
		return (2);
	else if (sphere->position.x < 0 && sphere->position.y < 0)
		return (3);
	else if (sphere->position.x > 0 && sphere->position.y < 0)
		return (4);
	return (0);
}

int	get_quadrant(t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_quadrant(obj->object));
	else if (obj->type == CYLINDER)
		return (cylinder_quadrant(obj->object));
	else if (obj->type == PLANE)
		return (plane_quadrant(obj->object));
	return (0);
}
