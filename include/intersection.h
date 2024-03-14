#ifndef INTERSECTION_H
# define INTERSECTION_H

#include "structs.h"

void		add_inter_list_back(t_inter_list **list, t_inter inter);
void		delete_inter_list(t_inter_list *list);
bool		intersection_bvh(t_bvh_node *node, t_inter_list **list, t_ray ray);
bool		find_closest_inter(t_inter *closest_inter, t_inter_list *list);

#endif
