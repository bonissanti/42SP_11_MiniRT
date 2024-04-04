#include "../../../include/test.h"

void	test_sphere(void)
{
	t_data	data;

	init_structs(&data);

	char	*test_line = "sp 0.0,0.0,20.6 12.6 10,0,255";
	int		result = analyze_sphere(test_line + 2, &data);

	if (result == ERROR)
		printf(RED "Falha no teste: Análise da esfera falhou\n"RESET);

	t_object *obj = data.objects;
	if (!obj || obj->type != SPHERE)
		printf(RED "Falha no teste: Nenhum objeto do tipo esfera foi adicionado");

	t_sphere *sphere = (t_sphere *)obj->object;
	
	check_equal_doubles_p(sphere->position.x, 0.0, "Posição x da esfera");
	check_equal_doubles_p(sphere->position.y, 0.0, "Posição y da esfera");
	check_equal_doubles_p(sphere->position.z, 20.6, "Posição z da esfera");
	check_equal_doubles_p(sphere->diameter, 12.6, "Diametro da esfera");
	check_equal_doubles_p(sphere->color[0], 10, "Cor r da esfera");
	check_equal_doubles_p(sphere->color[1], 0, "Cor g da esfera");
	check_equal_doubles_p(sphere->color[2], 255, "Cor b da esfera");
	
	#ifndef TEST_H
	printf("Printando matriz de transformação da esfera: \n");
	print_matrix(sphere->transform);
	printf("\nPrintando matriz de transformação invertida da esfera: \n");
	print_matrix(sphere->inversed_t);
	#endif /* ifndef TEST_H */
}

