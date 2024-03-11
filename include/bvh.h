/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:35:53 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/11 13:31:50 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}	t_aabb;

typedef struct s_obj
{
	t_aabb			bbox;
	void			*object;
}	t_obj;

typedef struct s_bvh_node
{
	t_obj				object;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
	t_aabb				bbox;
}	t_bvh_node;

t_aabb		get_bbox_sphere(t_sphere *sphere);
t_aabb		get_bbox_cylinder(t_cylinder *cylinder);
t_aabb		get_bbox_plane(t_plane *plane);

void		sort_by_position(t_object **objects, int start, int end);

t_bvh_node	*construct_bvh(t_object **objects, int start, int end);
t_object	*get_cur(t_object *objects, int start);

#endif //BVH_H