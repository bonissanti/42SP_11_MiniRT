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
