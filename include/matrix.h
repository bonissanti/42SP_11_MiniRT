#ifndef MATRIX_H
# define MATRIX_H

# include "structs.h"

// # Matrices

void		matrix_identity(t_matrix *mat);
t_matrix	*create_matrix(void);
void		set_camera_transform(t_camera *camera);
void		basic_invert_matrix(const t_matrix *original, t_matrix *inverted);
void		matrix_free(t_matrix *matrix);
t_coords	matrix_multiply_point(const t_matrix *m, const t_coords *point);
t_matrix	matrix_multiply(const t_matrix *a, const t_matrix *b);
t_matrix	matrix_translate(double tx, double ty, double tz);

#endif
