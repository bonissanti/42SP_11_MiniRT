#include "../../../include/test.h"

void	test_camera(void)
{
	t_data	data;

	init_structs(&data);

	char	*test_line = "C -50.0,0,20 0,0,1 70";
	int		result = analyze_camera(test_line + 1, &data);

	printf(F_WHITE"Test #2 - "RESET BOLD"Parser | Camera - start #1\n"RESET);

	compare_double(result, OK, "Retorno do analyze_camera");
	compare_double(data.camera.origin.x, -50, "Comparação da origem X");
	compare_double(data.camera.origin.y, 0, "Comparação da origem Y");
	compare_double(data.camera.origin.z, 20, "Comparação da origem Z");
	compare_double(data.camera.orientation.x, 0, "Comparação da orientação X");
	compare_double(data.camera.orientation.y, 0, "Comparação da orientação Y");
	compare_double(data.camera.orientation.z, 1, "Comparação da orientação Z");
	compare_double(data.camera.fov, (70 * M_PI) / 180, "Comparação do FOV");
	
	#ifndef TEST_H
	printf("Printando matriz de transformação preenchida: \n");
	print_matrix(data.camera.transform);
	printf("\nPrintando matriz de transformação invertida: \n");
	print_matrix(data.camera.inversed_t);
	#endif /* ifndef TEST_H */

	printf(F_WHITE"Test #2 - "RESET BOLD"Parser | Camera - end #1\n\n"RESET);

}
