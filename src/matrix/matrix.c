#include "../../include/minirt.h"

void	matrix_identity(t_matrix *mat)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			if (y == x)
				mat->matrix[y][x] = 1.0;
			else
			 	mat->matrix[y][x] = 0.0;
		}
	}
}

t_matrix	*create_matrix(void)
{
	t_matrix	*transform;

	transform = malloc(sizeof(t_matrix));
	if (!transform)
		return (NULL);
	matrix_identity(transform);
	return (transform);
}

void	matrix_free(t_matrix *matrix)
{
	if (matrix)
		free(matrix);
}
