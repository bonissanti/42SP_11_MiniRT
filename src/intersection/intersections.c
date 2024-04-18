/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:25 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 13:14:59 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

bool	find_closest_inter(t_inter *closest_inter, t_inter_list *list)
{
	bool			found;
	double			closest_t;
	t_inter_list	*current;

	if (!list)
		return (false);
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

// bool	find_closest_inter2(t_inter_list *head)
// {
// 	bool			found;
// 	t_inter_list	*current;
// 	double			current_closest_t;

// 	current = head;
// 	found = false;
// 	current_closest_t = INFINITY;
// 	while (current)
// 	{
// 		if (current->inter.t < current_closest_t && current->inter.t > EPSILON)
// 		{
// 			current_closest_t = current->inter.t;
// 			found = true;
// 		}
// 		current = current->next;
// 	}
// 	return (found);
// }
