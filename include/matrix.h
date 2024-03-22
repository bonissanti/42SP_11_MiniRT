#ifndef MATRIX_H
# define MATRIX_H

# include "structs.h"

// # Matrices

void		matrix_identity(t_matrix *mat);
void		set_camera_transform(t_camera *camera, t_vec3 up);
void		basic_invert_matrix(const t_matrix *original, t_matrix *inverted);
void		matrix_free(t_matrix *matrix);
t_matrix	*create_matrix(void);
t_coords	matrix_multiply_point(const t_matrix *m, const t_coords *point);
t_matrix	matrix_multiply (t_matrix *a, t_matrix *b);
t_matrix	translation_matrix(double tx, double ty, double tz);


// # Operations

t_matrix	scaling_matrix(double sx, double sy, double sz);

// # Inverted

/* double		det2x2(double a, double b, double c, double d); */
/* double		det3x3(double m[3][3]); */
double		calculate_cofactor(t_matrix *original, int i, int j);
t_matrix	cofactor_matrix(t_matrix *original);
double		calculate_minor(t_matrix *original, int row_ign, int col_ign);
void		submatrix(t_matrix *original, t_matrix *submatrix, int row_ign, int col_ign);
void	invert_matrix(t_matrix *original, t_matrix *inverted);
double	calculate_minor(t_matrix *original, int row_ign, int col_ign);
double	determinant(t_matrix *original);
t_matrix	transpose_matrix(t_matrix *original);

#endif
