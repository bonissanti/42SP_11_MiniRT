/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:16:39 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/13 19:43:49 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	print_objects(t_object *head)
{
	t_object	*current;
	t_sphere	*sphere;
	int			i;

	current = head;
	i = 0;
	printf("\nPrinting objects\n----------------\n");
	while (current != NULL)
	{
		sphere = (t_sphere *)current->object;
		printf("Object %d: %f %f %f\n", i, sphere->position.x,
			sphere->position.y, sphere->position.z);
		current = current->next;
		i++;
	}
}

void	traverseBVH(t_bvh_node *node, int depth)
{
	if (node == NULL)
	{
		return ;
	}
	// Print indentation based on depth
	for (int i = 0; i < depth; ++i)
	{
		printf("  ");
	}
	// Print node's bounding box coordinates
	if (node->object != NULL)
		printf("Leaf: (%.2f, %.2f, %.2f) - (%.2f, %.2f, %.2f)\n",
			node->bbox.min.x, node->bbox.min.y, node->bbox.min.z,
			node->bbox.max.x, node->bbox.max.y, node->bbox.max.z);
	else
		printf("Inner Node: (%.2f, %.2f, %.2f) - (%.2f, %.2f, %.2f)\n",
			node->bbox.min.x, node->bbox.min.y, node->bbox.min.z,
			node->bbox.max.x, node->bbox.max.y, node->bbox.max.z);
	// Traverse left and right subtrees
	traverseBVH(node->left, depth + 1);
	traverseBVH(node->right, depth + 1);
}

void print_scene_ascii_art(t_object *objects, t_camera *camera) {
    char grid[6][6];
    t_object *cur = objects;
	t_sphere *sphere;

    // Initialize grid with spaces
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            grid[i][j] = ' ';
        }
    }

    // Set objects in grid
    while (cur) {
		sphere = (t_sphere *)cur->object;
        int x = (int)(sphere->position.x) + 3;
        int y = (int)(sphere->position.y) + 3;
        grid[y][x] = '#';
        cur = cur->next;
    }
	int x = (int)(camera->point.x) + 3;
	int y = (int)(camera->point.y) + 3;
	grid[y][x] = 'C';

    // Print grid
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_mlx		mlx;
	// t_bvh_node	*node;

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
	print_scene_ascii_art(data.objects, &data.camera);
	// node = create_bvh(&data.objects);
	// traverseBVH(node, 0);
	render_scene(&data, &mlx);
	free_objects(data.objects);
	return (0);
}
