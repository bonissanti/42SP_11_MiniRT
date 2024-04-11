#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "structs.h"

# define MAX 1
# define MIN 0

void	print_inter_list(t_inter_list *list);
/* void		add_inter_list_back(t_inter_list **list, t_object *obj, double t); */
void		add_inter_list_back(t_inter_list **list, t_inter inter);
void		delete_inter_list(t_inter_list *list);
bool		intersection_bvh(t_bvh_node *node, t_inter_list **list, t_ray ray);
bool		find_closest_inter2(t_inter_list *head);
bool		find_closest_inter(t_inter *closest_inter, t_inter_list *list);
t_inter		config_inter(t_geo_u *geo, t_vec3 point, t_object *obj, double t[2]);
bool 		intersection_obj(t_object *object, t_ray *ray, t_inter_list **inter_list);

#endif
