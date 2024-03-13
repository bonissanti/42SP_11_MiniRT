/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:25 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 19:26:17 by brunrodr         ###   ########.fr       */
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
		left_hit = intersection_bvh(node->left, ray);
	if (node->right)
		right_hit = intersection_bvh(node->right, ray);
	if (!node->left || !node->right)
	{
		hit = check_inter_with_objection(node->object, ray);
		if (hit)
		{
			*closest_object = node->object;
			return (hit);
		}
	}
	return (left_hit || right_hit);

}
