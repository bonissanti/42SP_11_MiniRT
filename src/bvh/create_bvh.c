/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:29:22 by renato            #+#    #+#             */
/*   Updated: 2024/03/11 17:34:26 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_object	*get_cur(t_object *objects, int start)
{
	t_object	*cur;
	int			i;

	i = 0;
	cur = objects;
	while (i < start)
	{
		cur = cur->next;
		i++;
	}
	return (cur);
}

t_aabb	get_obj_bbox(t_object *obj)
{
	t_aabb	bbox;

	bbox.min.x = bbox.min.y = bbox.min.z = FLT_MIN;
	bbox.max.x = bbox.max.y = bbox.max.z = FLT_MAX;
	if (obj->type == SPHERE)
		bbox = get_bbox_sphere(obj->object);
	else if (obj->type == CYLINDER)
		bbox = get_bbox_cylinder(obj->object);
	else if (obj->type == PLANE)
		bbox = get_bbox_plane(obj->object);
	return (bbox);
}

t_aabb	calculate_bbox(t_object **objects, int start, int end)
{
	t_aabb		bbox;
	t_aabb		obj_bbox;
	t_object	*obj;

	obj = get_cur(*objects, start);
	// bbox.min.x = bbox.min.y = bbox.min.z = FLT_MAX;
	// bbox.max.x = bbox.max.y = bbox.max.z = FLT_MIN;
	for (int i = start; i < end; i++)
	{
		obj_bbox = get_obj_bbox(obj);
		bbox.min.x = fmin(bbox.min.x, obj_bbox.min.x);
		bbox.min.y = fmin(bbox.min.y, obj_bbox.min.y);
		bbox.min.z = fmin(bbox.min.z, obj_bbox.min.z);
		bbox.max.x = fmax(bbox.max.x, obj_bbox.max.x);
		bbox.max.y = fmax(bbox.max.y, obj_bbox.max.y);
		bbox.max.z = fmax(bbox.max.z, obj_bbox.max.z);
		obj = obj->next;
	}
	return (bbox);
}

t_bvh_node	*construct_bvh(t_object **objects, int start, int end)
{
	t_bvh_node	*node;
	int			count;
	int			mid;

	node = malloc(sizeof(t_bvh_node));
	node->bbox = calculate_bbox(objects, start, end);
	count = end - start;
	if (count == 1)
	{
		node->left = NULL;
		node->right = NULL;
		node->object.object = get_cur(*objects, start);
	}
	else
	{
		mid = start + count / 2;
		node->left = construct_bvh(objects, start, mid);
		node->right = construct_bvh(objects, mid, end);
		node->object.object = NULL;
	}
	return (node);
}

t_bvh_node	*create_bvh(t_object **objects)
{
	int			count;
	t_object	*cur;
	t_bvh_node	*root;

	count = 0;
	cur = *objects;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	root = construct_bvh(objects, 0, count);
	return (root);
}

bool	intersect_bvh_node(t_bvh_node *node, Ray ray, float *tNear,
	float *tFar)
{
	if (!intersectAABB(node->bbox, ray, tNear, tFar)) {
		return false;
	}
	if (node->object != NULL) {
		// Leaf node: Check intersection with the object
		return (intersectObject(node->object, ray, tNear, tFar));
	} else {
		// Internal node: Recursively check intersections with child nodes
		bool hitLeft = intersect_bvh_node(node->left, ray, tNear, tFar);
		bool hitRight = intersect_bvh_node(node->right, ray, tNear, tFar);
		return (hitLeft || hitRight);
	}
}
