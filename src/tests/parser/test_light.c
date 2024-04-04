#include "../../../include/test.h"

void	test_light(void)
{
	t_data data;

	init_structs(&data);

	char	*test_line = "L -40.0,50.0,0.0 0.6";
	int		result	= analyze_light(test_line + 1, &data);

	printf(F_WHITE"Test #2 - "RESET BOLD"Parser | Light - start #1\n"RESET);

	compare_double(result, OK, "Retorno do analyze_light");
	compare_double(data.light.position.x, -40.0, "Comparação da posição da luz X");
	compare_double(data.light.position.y, 50.0, "Comparação da posição da luz Y");
	compare_double(data.light.position.z, 0.0, "Comparação da posição da luz Z");
	compare_double(data.light.brightness, 0.6, "Comparação da brightness X");

	printf(F_WHITE"Test #2 - "RESET BOLD"Parser | Light - end #1\n"RESET);
}
