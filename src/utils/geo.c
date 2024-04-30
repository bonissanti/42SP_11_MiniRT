/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:30:11 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/30 12:44:45 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * Function: get_intersection_point
 * -------------------
 * Returns the intersection point of a ray with an object.
 * The intersection point is calculated by the physics formula:
 * 
 * intersection_point = ray.origin + ray.direction * t
 *
 * Where: 
 * - intersection_point is the point where the ray intersects the object.
 * - ray.origin is the origin of the ray.
 * - ray.direction is the direction of the ray.
 * - t is the distance from the origin to the intersection point.
 * 
 * @return: t_vec3, aka the intersection point in object space.
 */

t_vec3	get_intersection_point(t_ray ray, double t)
{
	t_vec3	intersection_point;

	intersection_point = (t_vec3){ray.origin.x + ray.direction.x * t,
		ray.origin.y + ray.direction.y * t, ray.origin.z + ray.direction.z * t};
	return (intersection_point);
}

/**
 * Function: get_geo
 * -------------------
 * This is a helper function that returns the object of the t_geo_u union.
 * Basically, it is a way to access the object of the union without having to
 * cast it every time. It checks the type of the object and returns the correct
 * object.
 *
 * @return: t_geo_u, aka the object of the union.
 */

t_geo_u	get_geo(t_object *object)
{
	t_geo_u	geo;

	if (object->type == SPHERE)
		geo.sphere = (t_sphere *)object->object;
	else if (object->type == PLANE)
		geo.plane = (t_plane *)object->object;
	else if (object->type == CYLINDER)
		geo.cylinder = (t_cylinder *)object->object;
	else
		geo.sphere = NULL;
	return (geo);
}
