/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:23:25 by rseelaen          #+#    #+#             */
/*   Updated: 2024/03/12 11:45:11 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	cylinder_quadrant(t_cylinder *cylinder)
{
	if (cylinder->position.x > 0 && cylinder->position.y > 0)
		return (1);
	else if (cylinder->position.x < 0 && cylinder->position.y > 0)
		return (2);
	else if (cylinder->position.x < 0 && cylinder->position.y < 0)
		return (3);
	else if (cylinder->position.x > 0 && cylinder->position.y < 0)
		return (4);
	return (0);
}

int	plane_quadrant(t_plane *plane)
{
	if (plane->position.x > 0 && plane->position.y > 0)
		return (1);
	else if (plane->position.x < 0 && plane->position.y > 0)
		return (2);
	else if (plane->position.x < 0 && plane->position.y < 0)
		return (3);
	else if (plane->position.x > 0 && plane->position.y < 0)
		return (4);
	return (0);
}

int	sphere_quadrant(t_sphere *sphere)
{
	if (sphere->position.x > 0 && sphere->position.y > 0)
		return (1);
	else if (sphere->position.x < 0 && sphere->position.y > 0)
		return (2);
	else if (sphere->position.x < 0 && sphere->position.y < 0)
		return (3);
	else if (sphere->position.x > 0 && sphere->position.y < 0)
		return (4);
	return (0);
}

int	get_quadrant(t_object *obj)
{
	if (obj->type == SPHERE)
		return (sphere_quadrant(obj->object));
	else if (obj->type == CYLINDER)
		return (cylinder_quadrant(obj->object));
	else if (obj->type == PLANE)
		return (plane_quadrant(obj->object));
	return (0);

}

double	get_magnitude(t_object *obj)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
	t_coords	pos;

	if (obj->type == SPHERE)
	{
		sphere = (t_sphere *)obj->object;
		pos = sphere->position;
	}
	else if (obj->type == CYLINDER)
	{
		cylinder = (t_cylinder *)obj->object;
		pos = cylinder->position;
	}
	else if (obj->type == PLANE)
	{
		plane = (t_plane *)obj->object;
		pos = plane->position;
	}
	return (sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z));
}

int	compare_position(t_object *obj1, t_object *obj2)
{
	int	mag1;
	int	mag2;

	mag1 = get_magnitude(obj1);
	mag2 = get_magnitude(obj2);
	if (mag1 < mag2)
		return (1);
	return (0);
}

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

void	sort_by_position(t_object **objects, int start, int end)
{
	t_object	*temp;
	t_object	*cur;
	t_object	*comp;
	int			i;
	int			j;

	cur = get_cur(*objects, start);
	i = start;
	j = end;
	while (cur->next)
	{
		comp = cur->next;
		while (comp)
		{
			// printf("\ncomparing\n");
			// printf("quadrant cur: %d\n", get_quadrant(cur));
			// printf("quadrant comp: %d\n", get_quadrant(comp));
			// printf("compare position: %d\n", compare_position(cur, comp));
			if (get_quadrant(cur) == get_quadrant(comp)
				&& compare_position(cur, comp) == 1)
			{
				printf("swapping\n");
				swap_nodes(objects, cur, comp);
				temp = cur;
				cur = comp;
				comp = temp;
			}
			comp = comp->next;
			j++;
		}
		i++;
		cur = cur->next;
	}
    // printf("%d\n", cur->type);
	*objects = get_cur(*objects, start);
}
