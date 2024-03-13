/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:35:53 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/13 17:27:24 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "structs.h"

t_aabb		get_obj_bbox(t_object *obj);

void		quick_sort(t_object *first, t_object *last);
t_object	*get_last(t_object *cur);

t_bvh_node	*create_bvh(t_object **objects);
t_object	*get_cur(t_object *objects, int start);

int			get_quadrant(t_object *obj);

// _Bool		intersection_bvh(t_bvh_node *node, t_ray ray,
// 				t_object **closest_object);

#endif //BVH_H
