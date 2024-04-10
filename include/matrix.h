#ifndef MATRIX_H
# define MATRIX_H

# include "structs.h"

// # Matrices
void		matrix_identity(t_matrix *mat);
void		set_camera_transform(t_camera *camera, t_coords from, t_vec3 forward, t_vec3 up);
void		basic_invert_matrix(const t_matrix *original, t_matrix *inverted);
void		matrix_free(t_matrix *matrix);
t_coords	matrix_multiply_point(t_matrix m, const t_coords point);
t_matrix	*create_matrix(void);
t_matrix	matrix_multiply (t_matrix *a, t_matrix *b);
t_matrix	translation_matrix(double tx, double ty, double tz);

// # Operations
t_quatern	create_rotation_quatern(t_vec3 orientation, double radians);
t_matrix	quatern_to_matrix(t_vec3 orientation, double radians);
t_matrix	get_rotation_matrix(t_vec3 orientation);

//WARNING: As três funções acima não estão sendo utilizadas 
t_matrix	verify_orientation(t_vec3 orientation);
t_matrix	scaling_matrix(double sx, double sy, double sz);
t_matrix	rotation_xy(double x_angle, double y_angle);
t_matrix	rotation_zx(double z_angle, double x_angle);
t_matrix	rotation_matrix_y(double angle);
t_matrix	rotation_matrix_x(double angle);
t_matrix	rotation_matrix_z(double angle);

// # Inverted
void		submatrix(t_matrix *original, t_matrix *submatrix, int row_ign, int col_ign);
void		invert_matrix(t_matrix *original, t_matrix *inverted);
double		calculate_cofactor(t_matrix *original, int i, int j);
double		calculate_minor(t_matrix *original, int row_ign, int col_ign);
double		calculate_minor(t_matrix *original, int row_ign, int col_ign);
double		determinant(t_matrix *original);
t_matrix	cofactor_matrix(t_matrix *original);
t_matrix	transpose_matrix(t_matrix *original);

#endif
