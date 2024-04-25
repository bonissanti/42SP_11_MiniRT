/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:30 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 11:42:32 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	add_objects(t_data *data, void *obj, t_object_type type)
{
	t_object	*new_obj;

	new_obj = malloc(sizeof(t_object));
	if (!new_obj)
		return (-1);
	new_obj->type = type;
	new_obj->object = obj;
	if (!data->objects)
		new_obj->next = NULL;
	else
		new_obj->next = data->objects;
	data->objects = new_obj;
	return (OK);
}

void	free_objects(t_object *objects)
{
	t_object	*current;
	t_object	*next;

	current = objects;
	while (current)
	{
		next = current->next;
		free(current->object);
		free(current);
		current = next;
	}
}

void	add_to_list(t_object *cur, double t, t_inter_list **inter_list)
{
	add_inter_list_back(inter_list, (t_inter){t, (t_vec3){0, 0, 0}, (t_vec3){0,
		0, 0}, cur});
}
