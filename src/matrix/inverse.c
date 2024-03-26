#include "../../include/minirt.h"



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
	while (++i < original->rows)
	{
		j = -1;
		l = 0;
		if (i == row_ign)
			continue;
		while (++j < original->cols)
		{
			if (j == col_ign)
				continue;
			submatrix->matrix[k][l++] = original->matrix[i][j];
		}
		k++;
	}
}

void	print_matrix(t_matrix to_test)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			printf("%f ", to_test.matrix[y][x]);
		printf("\n");
	}
}

double	determinant(t_matrix *original)
{
	int		j;
	double	det;
	double	cofactor;

	if (original->rows == 1)
		return (original->matrix[0][0]);
	
	j = -1;
	det = 0;
	while (++j < original->rows)
	{
		cofactor = calculate_cofactor(original, 0, j);
		det += original->matrix[0][j] * cofactor;
	}
	return (det);
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

//TODO: Testar cada função individualmente
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
