/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:38:15 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 12:41:27 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "structs.h"

// # Matrices
void		matrix_identity(t_matrix *mat);
void		set_camera_transform(t_camera *camera, t_coords from,
				t_vec3 forward, t_vec3 up);
void		basic_invert_matrix(const t_matrix *original, t_matrix *inverted);
t_coords	matrix_multiply_coords(t_matrix original, const t_coords coords);
t_matrix	matrix_multiply(t_matrix *a, t_matrix *b);
t_matrix	translation_matrix(double tx, double ty, double tz);

// # Operations
t_matrix	verify_orientation(t_vec3 orientation);
t_matrix	scaling_matrix(double sx, double sy, double sz);
t_matrix	arbitrary_rotation_xy(double x_angle, double y_angle);
t_matrix	arbitrary_rotation_zx(double z_angle, double x_angle);
t_matrix	simple_rotation_y(double angle);
t_matrix	simple_rotation_x(double angle);
t_matrix	simple_rotation_z(double angle);

// # Inverted
void		create_submatrix(t_matrix *original, t_matrix *submatrix,
				int row_ign, int col_ign);
void		invert_matrix(t_matrix *original, t_matrix *inverted);
double		calculate_cofactor(t_matrix *original, int i, int j);
double		calculate_minor(t_matrix *original, int row_ign, int col_ign);
double		calculate_minor(t_matrix *original, int row_ign, int col_ign);
double		determinant(t_matrix *original);
t_matrix	cofactor_matrix(t_matrix *original);
t_matrix	transpose_matrix(t_matrix *original);

// # Rotation
t_matrix	simple_rotation_y(double angle);
t_matrix	simple_rotation_z(double angle);
t_matrix	simple_rotation_x(double angle);
t_matrix	arbitrary_rotation_xy(double x_angle, double y_angle);
t_matrix	arbitrary_rotation_zx(double z_angle, double x_angle);

#endif
