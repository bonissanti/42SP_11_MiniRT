/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:16:39 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 17:55:05 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void print_objects(t_object* head) {
    t_object* current = head;
	t_sphere *sphere;
    int i = 0;
	printf("\nPrinting objects\n----------------\n");
    while (current != NULL) {
		sphere = (t_sphere *)current->object;
        printf("Object %d: %f %f %f\n", i, sphere->position.x, sphere->position.y, sphere->position.z);
        current = current->next;
        i++;
    }
}

void traverseBVH(t_bvh_node *node, int depth) {
	if (node == NULL) {
		return;
	}

	// Print indentation based on depth
	for (int i = 0; i < depth; ++i) {
		printf("  ");
	}

	// Print node's bounding box coordinates
	if (node->object != NULL)
		printf("Leaf: (%.2f, %.2f, %.2f) - (%.2f, %.2f, %.2f)\n", node->bbox.min.x,
				 node->bbox.min.y, node->bbox.min.z, node->bbox.max.x, node->bbox.max.y,
				 node->bbox.max.z);
	else
		printf("Inner Node: (%.2f, %.2f, %.2f) - (%.2f, %.2f, %.2f)\n", node->bbox.min.x,
				 node->bbox.min.y, node->bbox.min.z, node->bbox.max.x, node->bbox.max.y,
				 node->bbox.max.z);

	// Traverse left and right subtrees
	traverseBVH(node->left, depth + 1);
	traverseBVH(node->right, depth + 1);
}

int main(int argc, char **argv) 
{
	t_data		data;
	t_mlx		mlx;

	init_structs(&data);
	if (argc != 2) 
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	else if (valid_file(argv[1], &data) == ERROR)
		return (1);
	else if (parse_lines(&data) == ERROR)
		return (1);
	print_objects(data.objects);
	t_bvh_node *node = create_bvh(&data.objects);
	print_objects(data.objects);
	traverseBVH(node, 0);
	render_scene(&data, &mlx);
	free_objects(data.objects);
	return (0);
}
