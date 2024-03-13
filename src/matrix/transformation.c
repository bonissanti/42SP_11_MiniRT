/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:26 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:37:27 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	set_camera_transform(t_camera *camera)
{
	t_vec3	point_vec = {camera->point.x, camera->point.y, camera->point.z};
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	t_matrix	transform;

	matrix_identity(&transform);
	forward = normalize_vector(subtract_vector(camera->vector, point_vec));
	up = normalize_vector(camera->up);
	right = (normalize_vector(cross_vector(up, forward)));
	transform.matrix[0][0] = right.x;
	transform.matrix[0][1] = right.y;
	transform.matrix[0][2] = right.z;
	transform.matrix[1][0] = up.x;
	transform.matrix[1][1] = up.y;
	transform.matrix[1][2] = up.z;
	transform.matrix[2][0] = -forward.x;
	transform.matrix[2][1] = -forward.y;
	transform.matrix[2][2] = -forward.z;
	transform.matrix[3][0] = -dot_product(right, point_vec);
	transform.matrix[3][1] = -dot_product(up, point_vec);
	transform.matrix[3][2] = dot_product(forward, point_vec);
	transform.matrix[3][3] = 1.0;
	camera->transform = transform;
	basic_invert_matrix(&camera->transform, &camera->inversed_t);
}

void	basic_invert_matrix(const t_matrix *original, t_matrix *inverted)
{
	int	i;
	int	j;

	i = -1;
	matrix_identity(inverted);

	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			inverted->matrix[i][j] = original->matrix[i][j];
	}

	inverted->matrix[3][0] = -(original->matrix[3][0] * inverted->matrix[0][0] +
							   original->matrix[3][1] * inverted->matrix[1][0] +
							   original->matrix[3][2] * inverted->matrix[2][0]);
	inverted->matrix[3][1] = -(original->matrix[3][0] * inverted->matrix[0][1] +
							   original->matrix[3][1] * inverted->matrix[1][1] +
							   original->matrix[3][2] * inverted->matrix[2][1]);
	inverted->matrix[3][2] = -(original->matrix[3][0] * inverted->matrix[0][2] +
							   original->matrix[3][1] * inverted->matrix[1][2] +
							   original->matrix[3][2] * inverted->matrix[2][2]);
}
