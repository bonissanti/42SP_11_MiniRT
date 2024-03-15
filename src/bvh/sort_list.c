/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:23:25 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/15 16:58:05 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	swap_nodes(t_object** head_ref, t_object *cur, t_object *comp)
{
	t_object* prevX = NULL;
	t_object* currX = *head_ref;
	t_object* prevY = NULL;
	t_object* currY = *head_ref;

	while (currX && currX != cur)
	{
		prevX = currX;
		currX = currX->next;
	}
	while (currY && currY != comp)
	{
		prevY = currY;
		currY = currY->next;
	}
	if (prevX != NULL)
		prevX->next = currY;
	else
		*head_ref = currY;
	if (prevY != NULL)
		prevY->next = currX;
	else
		*head_ref = currX;
	t_object* temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;
}

t_object	*partition(t_object **head, t_object *first, t_object *last)
{
	t_object	*pivot;
	t_object	*cur;
	t_object	*comp;

	pivot = last;
	cur = first;
	comp = first;
	while (comp != last)
	{
		if (get_quadrant(comp) < get_quadrant(pivot))
		{
			swap_nodes(head, cur, comp);
			cur = cur->next;
		}
		comp = comp->next;
	}
	swap_nodes(head, cur, last);
	return (cur);
}

t_object	*get_last(t_object *cur)
{
	while (cur && cur->next)
		cur = cur->next;
	return (cur);
}

void	quick_sort(t_object **head, t_object *first, t_object *last)
{
	t_object	*pivot;

	if (first == last)
		return ;
	pivot = partition(head, first, last);
	if (pivot && pivot->next && pivot->next != last)
		quick_sort(head, pivot->next, last);
	if (pivot && pivot != first && pivot != last)
		quick_sort(head, first, pivot);
}
