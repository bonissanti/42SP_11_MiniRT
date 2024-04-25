/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:25 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 18:45:22 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

bool	attempt_intersection(t_object *cur, t_ray *ray, double t[2],
						t_inter_list **inter_list)
{
	bool	last_hit;

	last_hit = false;
	if (cur->type == SPHERE)
		last_hit = hit_sphere(cur->object, ray_transform(*ray,
					get_geo(cur).sphere->inversed_t), t);
	else if (cur->type == PLANE)
		last_hit = hit_plane(ray_transform(*ray,
					get_geo(cur).plane->inversed_t), t);
	else if (cur->type == CYLINDER)
		last_hit = hit_cylinder(cur->object, ray_transform(*ray,
					get_geo(cur).cylinder->inversed_t), t);
	if (last_hit)
	{
		if (t[0] != t[1])
		{
			add_to_list(cur, t[0], inter_list);
			add_to_list(cur, t[1], inter_list);
		}
		else
			add_to_list(cur, t[0], inter_list);
		last_hit = false;
		return (true);
	}
	return (false);
}

bool	intersection_obj(t_object *object, t_ray *ray,
		t_inter_list **inter_list)
{
	t_object	*cur;
	bool		hit;
	double		t[2];

	cur = object;
	hit = false;
	ft_memset(&t, 0, sizeof(t));
	while (cur != NULL)
	{
		if (attempt_intersection(cur, ray, t, inter_list))
			hit = true;
		cur = cur->next;
	}
	return (hit);
}

bool	find_closest_inter(t_inter *closest_inter, t_inter_list *list)
{
	bool			found;
	double			closest_t;
	t_inter_list	*current;

	if (!list)
		return (false);
	found = false;
	current = list;
	closest_t = INFINITY;
	*closest_inter = (t_inter){.t = INFINITY, .object = NULL};
	while (current)
	{
		if (current->inter.t < closest_t && current->inter.t > EPSILON)
		{
			closest_t = current->inter.t;
			*closest_inter = current->inter;
			found = true;
		}
		current = current->next;
	}
	return (found);
}
