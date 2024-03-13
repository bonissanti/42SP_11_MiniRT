/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:25 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/13 18:11:10 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

_Bool	check_inter_with_objection(void *object, t_ray *ray)
{
	double		t_temp;	
	_Bool		hit;
	t_object	*obj;
	
	t_temp = 0.0; // distancia da interseção
	hit = false;
	obj = (t_object*)object;

	// if (obj->type == SPHERE)
	// 	hit = hit_sphere(obj->object, ray, &t_temp); // 
	// else if (obj->type == PLANE)
	// 	hit = hit_plane(obj->object, ray, &t_temp);
	// else
	//  	hit = hit_cylinder(obj->object, ray, &t_temp);
	if (hit && t_temp < ray->closest_t && t_temp > ray->t_min)
	{
		ray->closest_t = t_temp;
		ray->closest_object = obj;
		return (true);
	}
	return (false);
}

_Bool	intersection_aabb(t_aabb *bbox, t_ray ray)
{
	t_vec3	max;
	t_vec3	min;
	double	t[2];

	t[MIN] = -DBL_MAX;
	t[MAX] = DBL_MAX;
	min.x = (bbox->min.x - ray.origin.x) * ray.direction.x;
	max.x = (bbox->max.x - ray.origin.x) * ray.direction.x;
	min.y = (bbox->min.y - ray.origin.y) * ray.direction.y;
	max.y = (bbox->max.y - ray.origin.y) * ray.direction.y;
	min.z = (bbox->min.z - ray.origin.z) * ray.direction.z;
	max.z = (bbox->max.z - ray.origin.z) * ray.direction.z;
	t[MIN] = fmax(fmax(fmin(min.x, max.x), fmin(min.y, max.x)),
			fmin(min.z, max.z));
	t[MAX] = fmin(fmin(fmax(min.x, max.x), fmax(min.y, max.x)),
			fmax(min.z, max.z));
	if (t[MAX] < 0 || t[MIN] > t[MAX])
	{
		printf("x");
		return (false);
	}
	printf("o");
	return (true);
}

_Bool	intersection_bvh(t_bvh_node *node, t_ray ray, t_object **closest_object)
{
	_Bool	left_hit;
	_Bool	right_hit;
	_Bool	hit;

	left_hit = NULL;
	right_hit = NULL;

	if (!intersection_aabb(&node->bbox, ray)) // se não atingir o bolding box, pula fora
		return (NULL);
	if (node->left)
		left_hit = intersection_bvh(node->left, ray, closest_object);
	if (node->right)
		right_hit = intersection_bvh(node->right, ray, closest_object);
	if (!node->left || !node->right)
	{
		hit = check_inter_with_objection(node->object, &ray);
		if (hit)
		{
			*closest_object = node->object;
			return (hit);
		}
	}
	return (left_hit || right_hit);

}
