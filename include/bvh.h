/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:35:53 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/06 18:58:32 by rseelaen         ###   ########.fr       */
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

#endif //BVH_H