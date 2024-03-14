/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:25 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/14 17:26:37 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

bool	check_inter_with_object(void *object, t_ray *ray)
{
	double		t_temp;	
	bool		hit;
	t_object	*obj;
	
	t_temp = 0.0; // distancia da interseção
	hit = false;
	obj = (t_object*)object;

	if (obj->type == SPHERE)
		hit = hit_sphere(obj->object, ray, &t_temp); //
	// else if (obj->type == PLANE)
	// 	hit = hit_plane(obj->object, ray, &t_temp);
	// else
	//  hit = hit_cylinder(obj->object, ray, &t_temp);
	if (hit && t_temp < ray->closest_t && t_temp > EPSILON)
	{
		ray->closest_t = t_temp;
		ray->closest_object = obj;
		return (true);
	}
	return (false);
}

bool	intersection_bvh(t_bvh_node *node, t_inter_list **list, t_ray ray)
{
	bool	hit;
	t_inter	temp_inter;

	hit = false;
	ft_memset(&temp_inter, 0, sizeof(t_inter)); 
	// if (!intersection_aabb(&node->bbox, ray)) // se não atingir o bolding box, pula fora
	// 	return (false);
	
	if (!node->left && !node->right && node->object)
	{
		if (check_inter_with_object(node->object, &ray))
		{
			add_inter_list_back(list, temp_inter);
			hit = true;
		}
	}
	else 
	{
		hit |= intersection_bvh(node->left, list, ray);
		hit |= intersection_bvh(node->left, list, ray);
	}
	return (hit);
}

bool	find_closest_inter(t_inter *closest_inter, t_inter_list *list)
{
	bool	found;
	double	closest_t;
	t_inter_list *current;

	current = list;
	closest_t = INFINITY;
	*closest_inter = (t_inter){.t = INFINITY, .object = NULL};

	while (current)
	{
		if (current->inter.t < closest_t && current->inter.t > EPSILON)
		{
			closest_t = current->inter.t;
			*closest_inter = current->inter;
			found = true;
		}
		current = current->next;
	}
	return (found);
}
