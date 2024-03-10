/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:29:22 by renato            #+#    #+#             */
/*   Updated: 2024/03/10 14:41:38 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	cylinder_quadrant(t_cylinder *cylinder)
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

int	plane_quadrant(t_plane *plane)
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

int	sphere_quadrant(t_sphere *sphere)
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

double	get_magnitude(t_object *obj)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
	t_coords	pos;

	if (obj->type == SPHERE)
	{
		sphere = (t_sphere *)obj->object;
		pos = sphere->position;
	}
	else if (obj->type == CYLINDER)
	{
		cylinder = (t_cylinder *)obj->object;
		pos = cylinder->position;
	}
	else if (obj->type == PLANE)
	{
		plane = (t_plane *)obj->object;
		pos = plane->position;
	}
	return (sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z));
}

int	compare_position(t_object *obj1, t_object *obj2)
{
	int	mag1;
	int	mag2;

	mag1 = get_magnitude(obj1);
	mag2 = get_magnitude(obj2);
	if (mag1 < mag2)
		return (1);
	return (0);
}

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

t_object	*sort_by_position(t_object **objects, int start, int end, int axis)
{
	t_object	*temp;
	t_object	*cur;
	t_object	*comp;
	int			i;
	int			j;

	cur = get_cur(objects, start);
	while (cur && i++ < end)
	{
		comp = cur->next;
		while (comp && j++ < end)
		{
			if (get_quadrant(cur) == get_quadrant(comp)
				&& compare_position(cur, comp) == 1)
			{
				temp = cur;
				cur = comp;
				comp = temp;
			}
			comp = comp->next;
		}
		cur = cur->next;
	}
	return (get_cur(objects, start));
}

t_aabb	get_obj_bbox(t_object *obj)
{
	t_aabb	bbox;

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
	t_aabb	bbox;

	bbox.min.x = bbox.min.y = bbox.min.z = FLT_MAX;
	bbox.max.x = bbox.max.y = bbox.max.z = FLT_MIN;
	for (int i = start; i < end; i++)
	{
		t_object* obj = objects[i];
		// Assuming each object has a method to get its t_aabb
		t_aabb obj_bbox = get_obj_bbox(obj);
		// Update the bounding box min and max points
		bbox.min.x = fmin(bbox.min.x, obj_bbox.min.x);
		bbox.min.y = fmin(bbox.min.y, obj_bbox.min.y);
		bbox.min.z = fmin(bbox.min.z, obj_bbox.min.z);

		bbox.max.x = fmax(bbox.max.x, obj_bbox.max.x);
		bbox.max.y = fmax(bbox.max.y, obj_bbox.max.y);
		bbox.max.z = fmax(bbox.max.z, obj_bbox.max.z);
	}
	return (bbox);
}

t_bvh_node	*construct_bvh(t_object **objects, int start, int end)
{
	t_bvh_node* node = malloc(sizeof(t_bvh_node));
	// Calculate the bounding box for the current set of objects
	node->bbox = calculate_bbox(objects, start, end);

	int count = end - start;
	if (count == 1)
	{
		// Leaf node
		node->left = NULL;
		node->right = NULL;
		node->object.object = objects[start];
	}
	else
	{
		// Internal node
		int mid = start + count / 2;
		// Split objects into two groups
		node->left = construct_bvh(objects, start, mid);
		node->right = construct_bvh(objects, mid, end);
		node->object.object = NULL;
	}
	return (node);
}

void	create_bvh_test(t_object **objects, int count)
{
	t_bvh_node* root = construct_bvh(objects, 0, count);
	// Now we can use the root node to traverse the BVH tree
	// and check for ray intersections
	// ...
}

// bool	intersect_bvh_node(t_bvh_node *node, Ray ray, float *tNear,
// 	float *tFar)
// {
// 	if (!intersectAABB(node->bbox, ray, tNear, tFar)) {
// 		return false;
// 	}
// 	if (node->object != NULL) {
// 		// Leaf node: Check intersection with the object
// 		return (intersectObject(node->object, ray, tNear, tFar));
// 	} else {
// 		// Internal node: Recursively check intersections with child nodes
// 		bool hitLeft = intersect_bvh_node(node->left, ray, tNear, tFar);
// 		bool hitRight = intersect_bvh_node(node->right, ray, tNear, tFar);
// 		return (hitLeft || hitRight);
// 	}
// }
