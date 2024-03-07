/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bvh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:29:22 by renato            #+#    #+#             */
/*   Updated: 2024/03/07 00:56:21 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_aabb calculate_bbox(t_object** objects, int start, int end)
{
    t_aabb bbox;

    bbox.min.x = bbox.min.y = bbox.min.z = FLT_MAX;
    bbox.max.x = bbox.max.y = bbox.max.z = FLT_MIN;
    for (int i = start; i < end; i++) {
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
    return bbox;
}

t_bvh_node* construct_bvh(t_object** objects, int start, int end) {
    t_bvh_node* node = malloc(sizeof(t_bvh_node));
    // Calculate the bounding box for the current set of objects
    node->bbox = calculate_bbox(objects, start, end);

    int count = end - start;
    if (count == 1) {
        // Leaf node
        node->left = NULL;
        node->right = NULL;
        node->object = objects[start];
    } else {
        // Internal node
        int mid = start + count / 2;
        // Split objects into two groups
        node->left = construct_bvh(objects, start, mid);
        node->right = construct_bvh(objects, mid, end);
        node->object = NULL;
    }
    return node;
}

bool intersect_bvh_node(t_bvh_node* node, Ray ray, float* tNear, float* tFar) {
    if (!intersectAABB(node->bbox, ray, tNear, tFar)) {
        return false;
    }

    if (node->object != NULL) {
        // Leaf node: Check intersection with the object
        return intersectObject(node->object, ray, tNear, tFar);
    } else {
        // Internal node: Recursively check intersections with child nodes
        bool hitLeft = intersect_bvh_node(node->left, ray, tNear, tFar);
        bool hitRight = intersect_bvh_node(node->right, ray, tNear, tFar);
        return hitLeft || hitRight;
    }
}