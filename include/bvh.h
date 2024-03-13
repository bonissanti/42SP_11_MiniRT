/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:35:53 by rseelaen          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/03/12 17:50:35 by rseelaen         ###   ########.fr       */
=======
/*   Updated: 2024/03/12 17:15:09 by brunrodr         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

<<<<<<< Updated upstream
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
	t_object_type		type;
	void				*object;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
	t_aabb				bbox;
}	t_bvh_node;
=======
# include "structs.h"
>>>>>>> Stashed changes

t_aabb		get_obj_bbox(t_object *obj);

void		quick_sort(t_object *first, t_object *last);
t_object	*get_last(t_object *cur);

t_bvh_node	*create_bvh(t_object **objects);
t_object	*get_cur(t_object *objects, int start);

<<<<<<< Updated upstream
int			get_quadrant(t_object *obj);

#endif //BVH_H
=======
#endif
>>>>>>> Stashed changes
