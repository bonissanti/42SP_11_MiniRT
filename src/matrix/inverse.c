#include "../../include/minirt.h"
#include <stdalign.h>



t_matrix	transpose_matrix(t_matrix *original)
{
	int			i;
	int			j;
	t_matrix	transposed;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			transposed.matrix[i][j] = original->matrix[j][i];
	}
	return (transposed);
}

void	create_submatrix(t_matrix *original, t_matrix *submatrix, int row_ign, int col_ign)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = -1;
	k = 0;
	submatrix->rows = original->rows - 1;
	submatrix->cols = original->cols - 1;
	while (++i < original->rows)
	{
		j = -1;
		l = 0;
		if (k == row_ign)
			continue;
		while (++j < original->cols)
		{
			if (l == col_ign)
				continue;
			submatrix->matrix[k][l++] = original->matrix[i][j];
		}
		k++;
	}
}

double	calculate_minor(t_matrix *original, int row_ign, int col_ign)
{
	t_matrix	submatrix;
	double		minor;

	submatrix.rows = original->rows - 1;
	submatrix.cols = original->cols - 1;

	create_submatrix(original, &submatrix, row_ign, col_ign);
	minor = determinant(&submatrix);

	return (minor);
}

double	calculate_cofactor(t_matrix *original, int i, int j)
{
	double	minor;

	minor = calculate_minor(original, i, j);
	if ((i + j) % 2 == 0)
		return (minor);
	else
	 	return ((-1) * minor);
}



t_matrix cofactor_matrix(t_matrix *original)
{
	int	i;
	int	j;
	t_matrix	cofactor;

	i = -1;
	while (++i < original->rows)
	{
		j = -1;
		while (++j < original->cols)
			cofactor.matrix[i][j] = calculate_cofactor(original, i, j);
	}
	return (cofactor);
}

void	invert_matrix(t_matrix *original, t_matrix *inverted)
{
	int			i;
	int			j;
	double		det;
	t_matrix	cofactor;
	t_matrix	transposed;

	det = determinant(original);
	if (det == 0)
		return ;

	cofactor = cofactor_matrix(original);
	transposed = transpose_matrix(&cofactor);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			inverted->matrix[i][j] = transposed.matrix[i][j] / det;
	}

}
