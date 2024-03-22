/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:26 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/20 16:55:15 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	set_camera_transform(t_camera *camera, t_vec3 up)
{
	t_matrix	transform;
	t_matrix	translation;

	matrix_identity(&camera->inversed_t);
	t_vec3	from_coords_to_vec = {camera->origin.x, camera->origin.y, camera->origin.z};
	t_vec3	to = camera->orientation;

	t_vec3	forward = normalize_vector(subtract_vector(to, from_coords_to_vec));
	t_vec3	left = cross_vector(forward, normalize_vector(up));
	t_vec3  true_up = cross_vector(left, forward);

	// orientation
	transform.matrix[0][0] = left.x;
	transform.matrix[0][1] = left.y;
	transform.matrix[0][2] = left.z;
	transform.matrix[1][0] = true_up.x;
	transform.matrix[1][1] = true_up.y;
	transform.matrix[1][2] = true_up.z;
	transform.matrix[2][0] = -forward.x;
	transform.matrix[2][1] = -forward.y;
	transform.matrix[2][2] = -forward.z;
	transform.matrix[3][3] = 1;
	// translation + multiply_matrix
	
	translation = translation_matrix(-from_coords_to_vec.x, -from_coords_to_vec.y, -from_coords_to_vec.z);
	camera->transform = matrix_multiply(&transform, &translation);

# ifndef TEST
	printf("Matrix original\n");
	print_matrix(camera->transform);
	printf("\n");
	// invert_matrix(&camera->transform, &camera->inversed_t);
	// printf("Inverted\n");
	// print_matrix(camera->inversed_t);
	// printf("\n");
# endif
}

// t_matrix	multiply_matrix(t_matrix a, t_matrix b)
// {
// 	int			y;
// 	int			x;
// 	int			i;
// 	t_matrix	result;
//
// 	y = -1;
// 	while (++y < 4)
// 	{
// 		x = -1;
// 		while (++x < 4)
// 		{
// 			i = -1;
// 			while (++i < 4)
// 				result.matrix[y][x] += a.matrix[y][i] * b.matrix[i][x];
// 		}
// 	}
// 	return (result);
// }
