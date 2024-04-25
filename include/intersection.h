/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:38:09 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 13:03:07 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "structs.h"

# define MAX 1
# define MIN 0

void	add_inter_list_back(t_inter_list **list, t_inter inter);
void	delete_inter_list(t_inter_list *list);
bool	intersection_bvh(t_bvh_node *node, t_inter_list **list, t_ray ray);
t_comps	prepare_comps(t_inter inter, t_ray ray);
bool	find_closest_inter(t_inter *closest_inter, t_inter_list *list);
t_inter	config_inter(t_geo_u *geo, t_vec3 point, t_object *obj, double t[2]);
bool	intersection_obj(t_object *object, t_ray *ray,
			t_inter_list **inter_list);
bool	intersect_caps(const t_cylinder *cyl, t_ray ray, double t[2]);

#endif
