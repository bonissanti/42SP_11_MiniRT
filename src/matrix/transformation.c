/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:26 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/27 12:12:55 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * Function: Set_camera_transform
 * --------------------
 * Sets up the camera transformation matrices in a ray tracing system context.
 * This function defines both the transformation matrix and its inverse, which
 * are critical for calculating the viewing rays from the camera to objects
 * in the 3D scene. The camera's transformation is established based on the
 * orientation provided by the 'from' parameter (the camera's origin),
 * 'forward' (the direction the camera is pointing towards), and 'up' (the
 * camera's up direction), allowing for the creation of an orthogonal basis
 * for viewing.
 *
 * @param camera: A strucute representing the camera. This will be modified by
 * the function to include the calculated matrices.
 * @param from: The position in 3D space from where the camera views the scene.
 * @param forward: The direction towards which the camera is pointed.
 * @param up: The approximate "up" direction for the camera, used to stabilize
 * the orientation.
 *
 * Process:
 * 1. Calculates the 'left' vector as the cross product between 'forward' and
 * 		the normalization of 'up', establishing an axis orthogonal to the viewing
 * 		direction and the up vector.
 * 2. Recalculates 'up' (true_up) as the cross product between 'left' and
 * 		'forward' to ensure orthogonality and correctness of the basis.
 * 3. Constructs the camer's orientation matrix based on the 'left', 'true_up'
 * 		and 'forward' vectors.
 * 4. Calculates the translation matrix to position the camera at the origin ('from')
 * 		of the view.
 * 5. Calculates and stores the inverse of the transformation matrix, essential for
 * 		ray transformations during the ray tracing process.
 *
 * @return: This function does not return a value. Instead, it directly modifies the
 * 'camera' structure passed as a parameter.
 */

void	set_camera_transform(t_camera camera, t_coords from, t_vec3 forward, t_vec3 up)
{
	t_vec3	left;
	t_vec3	true_up;
	t_matrix transform;
	t_matrix translation;
	t_matrix orientation;

	matrix_identity(&orientation);
	left = cross_vector(forward, normalize_vector(up));
	true_up = cross_vector(left, forward);

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
	transform.matrix[3][3] = 1.0;


	//translation + multiply_matrix
	translation = translation_matrix(-from.x, -from.y, -from.z);
	camera.transform = matrix_multiply(&transform, &translation);

	matrix_identity(&camera.inversed_t);
	invert_matrix(&camera.transform, &camera.inversed_t);
}


//TODO: Adicionar funções para configurar matrizes dos objetos, incluindo a inversão da matriz
t_matrix	transform_sphere(t_coords coords, double radius)
{
	t_matrix	transform;
	t_matrix	translation;
	t_matrix	scaling;

	scaling = scaling_matrix(radius, radius, radius);
	translation = translation_matrix(coords.x, coords.y, coords.z);
	transform = matrix_multiply(&translation, &scaling);
	return (transform);
}
