#include "../../include/minirt.h"

void	add_inter_list_back(t_inter_list **list, t_inter inter)
{
	t_inter_list	*new_node;
	t_inter_list	*current;

	new_node = (t_inter_list *)malloc(sizeof(t_inter_list));
	if (!new_node)
		return ;
	new_node->inter = inter;
	new_node->next = NULL;

	if (*list == NULL)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

t_inter	config_inter(t_geo_u *geo, t_vec3 point, t_object *obj, double t[2])
{
	t_inter	inter;

	inter.t[0] = t[0];
	inter.t[1] = t[1];
	inter.point = point;
	
	if (obj->type == SPHERE)
	{
		inter.normal.x = geo->sphere->position.x;
		inter.normal.y = geo->sphere->position.y;
		inter.normal.z = geo->sphere->position.z;
		inter.object = obj;
	}
	else if (obj->type == CYLINDER)
	{
		inter.normal.x = geo->cylinder->position.x;
		inter.normal.y = geo->cylinder->position.y;
		inter.normal.z = geo->cylinder->position.z;
		inter.object = obj;
	}
	else 
	{
		inter.normal.x = geo->plane->position.x;
		inter.normal.y = geo->plane->position.y;
		inter.normal.z = geo->plane->position.z;
		inter.object = obj;
	}
	return (inter);
}

void	delete_inter_list(t_inter_list *list)
{
	t_inter_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}
