#include "../../../include/test.h"

void	check_equal_doubles_p(double a, double b, const char *testName)
{
	if (fabs(a - b) < EPSILON)
		printf(GREEN "Sucesso no teste: " RESET L_GRAY "%s: Valores são iguais, valor de %f\n" RESET, testName, a);
	else
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado deveria ser maior que 0, mas foi %f\n"BOLD, testName, a);
}

void fabs_nonzero(double num, const char *testName)
{
	if (fabs(num) < EPSILON)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Determinante deveria ser diferente de 0, mas foi %f\n"BOLD, testName, num);
	else
		printf(GREEN "Sucesso no teste: " RESET L_GRAY "%s: Determinante diferente de 0, valor de %f\n" RESET, testName, num);
}

void	test_determinant(void)
{
	t_matrix result;

	matrix_identity(&result);

	// teste com determinante maior que 0
	t_matrix mat2x2 = {.rows = 2, .cols = 2, .matrix = {{1, 5, 0, 0}, {-3, 2, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
	double det = determinant(&mat2x2);
	printf(F_WHITE"Test #11 - "RESET BOLD"Inverse | Determinante > 0 - start\n"RESET);
	fabs_nonzero(det, "Retorno do determinante");
	printf(F_WHITE"Test #11 - "RESET BOLD"Inverse | Determinante > 0 - end\n\n"RESET);

	// teste com determinante igual a 0, deve falhar
	t_matrix mat3x3 = {.rows = 3, .cols = 3, .matrix = {{1, 2, 3, 0}, {4, 5, 6, 0}, {7, 8, 9, 0}, {0, 0, 0, 0}}};
	det = determinant(&mat3x3);
	printf(F_WHITE"Test #11 - "RESET BOLD"Inverse | Determinante == 0 - start\n"RESET);
	fabs_nonzero(det, "Retorno do determinante == 0");
	printf(F_WHITE"Test #11 - "RESET BOLD"Inverse | Determinante == 0 - end\n\n"RESET);
}

void	test_cofactor_matrix(void)
{
	t_matrix mat = {.rows = 2, .cols = 2, .matrix = {{4, 7, 0, 0}, {2, 6, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
	t_matrix cofactor = cofactor_matrix(&mat);

	printf(F_WHITE"Test #12 - "RESET BOLD"Inverse | Determinante == 0 - start\n"RESET);
	check_equal_doubles_p(cofactor.matrix[0][0], 6.0, "Teste cofactor #1");
	check_equal_doubles_p(cofactor.matrix[0][1], -2.0, "Teste cofactor #2");
	check_equal_doubles_p(cofactor.matrix[1][0], -7.0, "Teste cofactor #3");
	check_equal_doubles_p(cofactor.matrix[1][1], 4.0, "Teste cofactor #4");
	printf(F_WHITE"Test #12 - "RESET BOLD"Inverse | Determinante == 0 - end\n\n"RESET);
}

void test_calculate_minor(void)
{
	t_matrix mat = {.rows = 3, .cols = 3, .matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
	double minor00 = calculate_minor(&mat, 0, 0);
	
	printf(F_WHITE"Test #13 - "RESET BOLD"Inverse | Minor - start\n"RESET);
	check_equal_doubles_p(minor00, -3, "Retorno do menor número");
	printf(F_WHITE"Test #13 - "RESET BOLD"Inverse | Minor - end\n\n"RESET);

	t_matrix mat2 = {.rows = 3, .cols = 3, .matrix = {{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}};
	double minor01 = calculate_minor(&mat, 0, 0);
	printf(F_WHITE"Test #13 - "RESET BOLD"Inverse | Minor - start\n"RESET);
	printf("%f\n", minor01);
	(void)mat2;
	check_equal_doubles_p(minor00, -3, "Retorno do menor número");
	printf(F_WHITE"Test #13 - "RESET BOLD"Inverse | Minor - end\n\n"RESET);
}
