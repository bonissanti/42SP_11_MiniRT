#include "../../../include/test.h"

void	compare_double(double actual, double expected, const char *testName)
{
	if (actual != expected)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, testName, expected, actual);
	else
		printf(GREEN"Sucesso no teste: "RESET L_GRAY"%s: %f == %f\n"RESET, testName, actual, expected);
}

void	test_analyze_amblight(void)
{
	t_data data;
	init_structs(&data);

	char *test_line = "A 0.2 255,255,255";
	int	result = analyze_amblight(test_line + 1, &data);

	printf(F_WHITE"Test #1 - "RESET BOLD"Parser | Amblight 1 - start\n"RESET);
	
	compare_double(result, OK, "Retorno do analyze_amblight");
	compare_double(data.amblight.ratio, 0.2, "Comparação do ratio");
	compare_double(data.amblight.color[0], 255, "Comparação do R");
	compare_double(data.amblight.color[1], 255, "Comparação do G");
	compare_double(data.amblight.color[2], 255, "Comparação do B");

	printf(F_WHITE"\nTest #1 - "RESET BOLD"Parser | Amblight 1 - end\n\n"RESET);	
}

