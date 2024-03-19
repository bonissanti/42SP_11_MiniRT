/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:25 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/19 13:37:01 by rseelaen         ###   ########.fr       */
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

_Bool	intersection_aabb(t_aabb *bbox, t_ray ray)
{
	t_vec3	max;
	t_vec3	min;
	double	t[2];

	t[MIN] = -DBL_MAX;
	t[MAX] = DBL_MAX;
	min.x = (bbox->min.x - ray.origin.x) / ray.direction.x;
	max.x = (bbox->max.x - ray.origin.x) / ray.direction.x;
	min.y = (bbox->min.y - ray.origin.y) / ray.direction.y;
	max.y = (bbox->max.y - ray.origin.y) / ray.direction.y;
	min.z = (bbox->min.z - ray.origin.z) / ray.direction.z;
	max.z = (bbox->max.z - ray.origin.z) / ray.direction.z;
	t[MIN] = fmax(fmax(fmin(min.x, max.x), fmin(min.y, max.y)),
			fmin(min.z, max.z));
	t[MAX] = fmin(fmin(fmax(min.x, max.x), fmax(min.y, max.y)),
			fmax(min.z, max.z));
	if (t[MAX] < 0 || t[MIN] > t[MAX])
		return (false);
	return (true);
}

t_vec3	get_intersection_point(t_ray ray, double t)
{
	t_vec3	intersection_point;

	intersection_point = (t_vec3){ray.origin.x + t * ray.direction.x,
		ray.origin.y + t * ray.direction.y,
		ray.origin.z + t * ray.direction.z};
	return (intersection_point);
}

t_vec3	get_normal(t_vec3 point, t_vec3 center)
{
	t_vec3	normal;

	normal = subtract_vector(point, center);
	normalize_vector(normal);
	return (normal);
}

bool	intersection_bvh(t_bvh_node *node, t_inter_list **list, t_ray ray)
{
	bool	hit;
	t_inter	temp_inter;

	hit = false;
	ft_memset(&temp_inter, 0, sizeof(t_inter));
	if (!intersection_aabb(&node->bbox, ray))
		return (false);
	if (!node->left && !node->right && node->object)
	{
		if (check_inter_with_object(node->object, &ray))
		{
			temp_inter.t = ray.closest_t;
			temp_inter.object = node->object;
			temp_inter.point = get_intersection_point(ray, temp_inter.t);
			t_sphere* sphere = (t_sphere*)node->object;
			temp_inter.normal = get_normal(temp_inter.point,
					(t_vec3){sphere->position.x, sphere->position.y,
					sphere->position.z});
			add_inter_list_back(list, temp_inter);
			hit = true;
		}
	}
	else
	{
		hit |= intersection_bvh(node->left, list, ray);
		hit |= intersection_bvh(node->right, list, ray);
	}
	return (hit);
}

bool	find_closest_inter(t_inter *closest_inter, t_inter_list *list)
{
	bool			found;
	double			closest_t;
	t_inter_list	*current;

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
