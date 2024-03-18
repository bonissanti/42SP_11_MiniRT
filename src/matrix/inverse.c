#include "../../include/minirt.h"
#include <stdalign.h>

void	transpose_matrix(t_matrix *original, t_matrix *transposed)
{
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			transposed->matrix[i][j] = original->matrix[j][i];
	}
}

double	determinant(t_matrix *original)
{
	int 	i;
	int		j;
	int		k;
	int		sub_col;
	double	det;
	double	submatrix[3][3];
	double cofactor;

	i = -1;
	det = 0.0;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			sub_col = 0;
			while (++k < 4)
			{
				if (k == i)
					continue;
				submatrix[j - 1][sub_col++] = original->matrix[j][k];
			}
		}

		if (i % 2 == 0)
			cofactor = 1 * original->matrix[0][i] * det3x3(submatrix);
		else
			cofactor = -1 * original->matrix[0][i] * det3x3(submatrix);
		det += cofactor;
	}
	return (det);
}

// f
void cofactor_matrix(t_matrix *matrix, t_matrix *cofactorMatrix)
{
	// analisa a submatriz para verificar as linhas e colunas 
	for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            double submatrix[3][3];
            // Preenche a submatriz 3x3
            for (int i = 0, sub_i = 0; i < 4; i++) {
                if (i == row) continue;
                for (int j = 0, sub_j = 0; j < 4; j++) {
                    if (j == col) continue;
                    submatrix[sub_i][sub_j++] = matrix->matrix[i][j];
                }
                sub_i++;
            }
            double cofactor = ((row + col) % 2 == 0 ? 1 : -1) * det3x3(submatrix);
            cofactorMatrix->matrix[row][col] = cofactor;
        }
    }
}
