/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:25 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/04 11:25:11 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

//BUG: O hit_sphere guarda a distancia mais proxima, mas num ray.origin (0,0,0) e ray.direction(0,0,1), o ponto do primeiro contato deverá ser negativo (-1)
// e o segundo é positivo (1), só que na lógica do closest_t, ele acaba guardando o segundo ponto (1). Talvez, devessemos guardar ambas interseções
bool	check_inter_with_object(void *object, t_ray *ray)
{
	double		t_temp;	
	bool		hit;
	t_object	*obj;
	t_sphere	*sphere;
	
	t_temp = 0.0; // distancia da interseção
	hit = false;
	obj = (t_object*)object;
	sphere = (t_sphere*)obj->object;
	t_ray temp_ray = ray_transform(*ray, &sphere->transform);
	
	if (obj->type == SPHERE)
		hit = hit_sphere(obj->object, &temp_ray, &t_temp);

	// else if (obj->type == PLANE)
	// 	hit = hit_plane(obj->object, ray, &t_temp);
	// else
	//  hit = hit_cylinder(obj->object, ray, &t_temp);
	if (hit && t_temp < ray->closest_t && t_temp > EPSILON)
	{
		printf("t_temp: %f\n", t_temp);
		ray->closest_t = t_temp;
		ray->closest_object = obj;
		return (true);
	}
	return (false);
}

bool intersection_aabb(t_aabb *bbox, t_ray ray, t_matrix *matrix)
{
	t_vec3 max;
	t_vec3 min;
	double t[2];

	t[MIN] = FLT_MAX;
	t[MAX] = FLT_MIN;
	// Apply inverse transformation to the ray
	t_ray transformed_ray = ray_transform(ray, matrix);
	min.x = (bbox->min.x - transformed_ray.origin.x) / transformed_ray.direction.x;
	max.x = (bbox->max.x - transformed_ray.origin.x) / transformed_ray.direction.x;
	min.y = (bbox->min.y - transformed_ray.origin.y) / transformed_ray.direction.y;
	max.y = (bbox->max.y - transformed_ray.origin.y) / transformed_ray.direction.y;
	min.z = (bbox->min.z - transformed_ray.origin.z) / transformed_ray.direction.z;
	max.z = (bbox->max.z - transformed_ray.origin.z) / transformed_ray.direction.z;
	t[MIN] = fmax(fmax(fmin(min.x, max.x), fmin(min.y, max.y)), fmin(min.z, max.z));
	t[MAX] = fmin(fmin(fmax(min.x, max.x), fmax(min.y, max.y)), fmax(min.z, max.z));
	if (t[MAX] < 0 || t[MIN] > t[MAX])
		return false;
	return true;
}

t_vec3	get_intersection_point(t_ray ray, double t)
{
	t_vec3	intersection_point;

	intersection_point = (t_vec3){ray.origin.x + t * ray.direction.x,
		ray.origin.y + t * ray.direction.y,
		ray.origin.z + t * ray.direction.z};
	return (intersection_point);
}

t_vec3	get_normal(t_vec3 point, t_vec3 center)
{
	t_vec3	normal;

	normal = subtract_vector(point, center);
	return (normalize_vector(normal));
}

bool	intersection_bvh(t_bvh_node *node, t_inter_list **list, t_ray ray)
{
	bool	hit;
	t_inter	temp_inter;
	t_geo_u	geo;
	t_ray	temp_ray;

	hit = false;
	ft_memset(&temp_inter, 0, sizeof(t_inter));
	if (!intersection_aabb(&node->bbox, ray, &node->inversed_t))
		return (false);
	if (!node->left && !node->right && node->object)
	{
		temp_ray = ray_transform(ray, &node->inversed_t);
		if (check_inter_with_object(node->object, &ray))
		{
			temp_inter.t = ray.closest_t;
			temp_inter.object = node->object;
			temp_inter.point = get_intersection_point(temp_ray, temp_inter.t);
			geo.sphere = (t_sphere *)(node->object);
			temp_inter.normal = get_normal(temp_inter.point,
					(t_vec3){geo.sphere->position.x, geo.sphere->position.y,
					geo.sphere->position.z});
			add_inter_list_back(list, temp_inter);
			hit = true;
		}
	}
	else
	{
		hit |= intersection_bvh(node->left, list, ray);
		hit |= intersection_bvh(node->right, list, ray);
	}
	return (hit);
}

bool	find_closest_inter(t_inter *closest_inter, t_inter_list *list)
{
	bool			found;
	double			closest_t;
	t_inter_list	*current;

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


// //PERF: Analise das versões simples + refatoramento:
//
// bool	find_closest_inter(t_inter *closest_inter, t_inter_list *head)
// {
// 	bool			found;
// 	double			closest_t;
// 	t_inter_list	*current;
//
// 	current = head;
// 	closest_t = INFINITY;
// 	*closest_inter = (t_inter){.t = INFINITY, .object = NULL};
//
// 	while (current)
// 	{
// 		if (current->inter.t < closest_t && current->inter.t > EPSILON)
// 		{
// 			closest_t = current->inter.t;
// 			*closest_inter = current->inter;
// 			found = true;
// 		}
// 		current = current->next;
// 	}
// 	return (found);
// }
//

// t_inter_list	*calculate_intersections(t_ray ray, t_object *objects)
// {
// 	int				num_intersections;
// 	t_inter_list	*intersections;
//
// 	intersections = NULL;
// 	while (objects)
// 	{
// 		if (objects->type == SPHERE)
// 			num_intersections = hit_sphere(objects, ray);
// 	}
// }
