#include "../../../include/test.h"

void	test_cylinder(void)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	char *test_line = "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255";
	int	result = analyze_cylinder(test_line + 2, &data);

	printf("Test #8 - Parser | Cylinder 1 - start\n");
	if (result == ERROR)
		printf(RED "Falha no teste: Análise do cilindro falhou\n"RESET);

	t_object *obj = data.objects;
	if (!obj || obj->type != CYLINDER)
		printf(RED "Falha no teste: Nenhum objeto do tipo cilindro foi adicionado");

	t_cylinder *cylinder = (t_cylinder *)obj->object;

	check_equal_doubles_p(cylinder->position.x, 50.0, "Posição x do cilindro");
	check_equal_doubles_p(cylinder->position.y, 0.0, "Posição y do cilindro");
	check_equal_doubles_p(cylinder->position.z, 20.6, "Posição z do cilindro");
	check_equal_doubles_p(cylinder->vector.x, 0.0, "Vetor x do cilindro");
	check_equal_doubles_p(cylinder->vector.y, 0.0, "Vetor y do cilindro");
	check_equal_doubles_p(cylinder->vector.z, 1.0, "Vetor z do cilindro");
	check_equal_doubles_p(cylinder->diameter, 14.2, "Diametro do cilindro");
	check_equal_doubles_p(cylinder->height, 21.42, "Altura do cilindro");
	check_equal_doubles_p(cylinder->color[0], 10, "Cor r do cilindro");
	check_equal_doubles_p(cylinder->color[1], 0, "Cor g do cilindro");
	check_equal_doubles_p(cylinder->color[2], 255, "Cor b do cilindro");
	check_equal_doubles_p(cylinder->max, 21.42 / 2, "Max do cilindro");
	check_equal_doubles_p(cylinder->min, -21.42 / 2, "Min do cilindro");
	
	#ifndef TEST_H
	printf("Printando matriz de transformação - Cilindro\n");
	print_matrix(cylinder->transform);
	printf("\nPrintando a inversa da matriz - Cilindro\n");
	print_matrix(cylinder->inversed_t);
	#endif /* ifndef TEST_H */

	printf("Test #8 - Parser | Cylinder 1 - end\n\n");
}
