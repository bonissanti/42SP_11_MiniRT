/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:35:53 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/15 16:52:57 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "structs.h"

t_aabb		get_obj_bbox(t_object *obj);

void		quick_sort(t_object **head, t_object *first, t_object *last);
t_object	*get_last(t_object *cur);

t_bvh_node	*create_bvh(t_object **objects);
t_object	*get_cur(t_object *objects, int start);

int			get_quadrant(t_object *obj);

#endif
