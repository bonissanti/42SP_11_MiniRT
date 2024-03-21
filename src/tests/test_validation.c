#include "../../include/test.h"

void	check_equal_ints(int result, int expected, const char *testName)
{
	if (result != expected)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %d, mas foi %d\n"BOLD, testName, expected, result);
	else
		printf(GREEN"Sucesso no teste: "RESET L_GRAY"%s: %d == %d\n"RESET, testName, result, expected);
}
void	test_validation(void)
{
	t_data data;
	

	ft_memset(&data, 0, sizeof(t_data));

	// arquivo não existe
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 1 - start\n"RESET);
	char *file = "./scenes/nonexistent_file.rt";
	int result = valid_file(file, &data);
	check_equal_ints(result, ERROR, "Arquivo não existente");
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 1 - end\n\n"RESET);	

	// arquivo existe
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 2 - start\n"RESET);
	char *file2 = "./scenes/teste_render.rt";
	int result2 = valid_file(file2, &data);
	check_equal_ints(result2, OK, "Arquivo válido");
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 2 - end\n\n"RESET);	

	// arquivo sem permissão
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 3- start\n"RESET);
	char *file3 = "./scenes/teste_without_permission.rt";
	int result3 = valid_file(file3, &data);
	check_equal_ints(result3, ERROR, "Arquivo sem permissão");
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 3 - end\n\n"RESET);	

	// arquivo vazio
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 4- start\n"RESET);
	char *file4 = "./scenes/teste_empty.rt";
	int result4 = valid_file(file4, &data);
	check_equal_ints(result4, ERROR, "Arquivo vazio");
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 4 - end\n\n"RESET);	

	//passando diretorio
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 4- start\n"RESET);
	char *file5 = "./scenes/teste_dir.rt";
	int result5 = valid_file(file5, &data);
	check_equal_ints(result5, ERROR, "Arquivo é um diretório");
	printf(F_WHITE"Test #0 - "RESET BOLD"Validation | File 4 - end\n\n"RESET);	
}
