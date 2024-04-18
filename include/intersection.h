/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:27:55 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 16:58:26 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "structs.h"

# define MAX 1
# define MIN 0

void	print_inter_list(t_inter_list *list);
void	add_inter_list_back(t_inter_list **list, t_inter inter);
void	delete_inter_list(t_inter_list *list);
bool	intersection_bvh(t_bvh_node *node, t_inter_list **list, t_ray ray);
bool	find_closest_inter2(t_inter_list *head);
bool	find_closest_inter(t_inter *closest_inter, t_inter_list *list);
t_geo_u	get_geo(t_object *object);
t_inter	config_inter(t_geo_u *geo, t_vec3 point, t_object *obj, double t[2]);
bool	intersection_obj(t_object *object, t_ray *ray,
			t_inter_list **inter_list);

#endif
