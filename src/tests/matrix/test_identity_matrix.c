#include "../../../include/test.h"

t_matrix	identity_example(void)
{
	t_matrix	example;

	ft_bzero(&example, sizeof(t_matrix));
	example.matrix[0][0] = 1;
	example.matrix[1][1] = 1;
	example.matrix[2][2] = 1;
	example.matrix[3][3] = 1;
	return (example);
}

void	check_equal_matrices(t_matrix result, t_matrix expected, const char *testName)
{
	int		y;
	int		x;
	bool	error;

	y = -1;
	error = false;
	print_matrix(expected);
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			if (fabs(result.matrix[y][x] - expected.matrix[y][x]) > EPSILON)
			{
				printf(RED"Falha no teste: "RESET L_GRAY"'%s': As matrizes são diferentes no ponto: esperado: %f | y = %d | x = %d e resultado: %f | y = %d | x = %d \n"BOLD, testName, expected.matrix[y][x], y, x, result.matrix[y][x], y, x);
				error = true;
			}
		}
	}
	if (!error)
		printf(GREEN"Sucesso no teste: "RESET L_GRAY"%s, as matrizes são iguais\n"RESET, testName);
}

void	compare_doubles(double result, double expected, const char *testName)
{
	if (result != expected)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, testName, expected, result);
	else
		printf(GREEN"Sucesso no teste: "RESET L_GRAY"%s: %f == %f\n"RESET, testName, result, expected);
}

void	test_identity_matrix(void)
{
	t_matrix result;

	matrix_identity(&result);
	t_matrix expected = identity_example();

	// comparativo
	printf(F_WHITE"Test #7 - "RESET BOLD"Matrix | Identity - start\n"RESET);
	check_equal_matrices(result, expected, "Comparação de identidades");
	printf(F_WHITE"Test #7 - "RESET BOLD"Matrix | Identity - end\n\n"RESET);	

	// teste com multiplicação
	t_coords point = {1, -99, 3};
	printf(F_WHITE"Test #7 - "RESET BOLD"Matrix | Identity and multiply - start\n"RESET);
	t_coords result2 = matrix_multiply_point(&result, &point);
	compare_doubles(result2.x, point.x, "Multiplicação de identidade - x");
	compare_doubles(result2.y, point.y, "Multiplicação de identidade - y");
	compare_doubles(result2.z, point.z, "Multiplicação de identidade - z");
	printf(F_WHITE"Test #7 - "RESET BOLD"Matrix | Identity and multiply - end\n\n"RESET);	

}

