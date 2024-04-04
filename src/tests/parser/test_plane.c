#include "../../../include/test.h"
#include <stdio.h>

void	test_plane(void)
{
	t_data	data;

	init_structs(&data);
	char	*test_line = "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225";
	int		result = analyze_plane(test_line + 2, &data);

	printf("Test #4 - Parser | Plano 1 - start\n");
	if (result == ERROR)
		printf(RED "Falha no teste: Análise do plano falhou\n"RESET);

	t_object *obj = data.objects;
	if (!obj || obj->type != PLANE)
		printf(RED "Falha no teste: Nenhum objeto do tipo plano foi adicionado");
	
	t_plane *plane = (t_plane *)obj->object;

	check_equal_doubles_p(plane->position.x, 50.0, "Posição x do plano"); 
	check_equal_doubles_p(plane->position.y, 0.0, "Posição y do plano"); 
	check_equal_doubles_p(plane->position.z, 20.6, "Posição z do plano"); 
	check_equal_doubles_p(plane->vector.x, 0.0, "Vetor x do plano");
	check_equal_doubles_p(plane->vector.y, 0.0, "Vetor y do plano");
	check_equal_doubles_p(plane->vector.z, 1.0, "Vetor z do plano");
	check_equal_doubles_p(plane->radius, 14.2, "Diametro do plano");
	check_equal_doubles_p(plane->color[0], 10, "Cor r do plano");
	check_equal_doubles_p(plane->color[1], 0, "Cor g do plano");
	check_equal_doubles_p(plane->color[2], 255, "Cor b do plano");

	#ifndef TEST_H
	printf("Printando a matriz de transformação do plano");
	print_matrix(plane->transform);
	printf("Printando a matriz de inversão do plano");
	print_matrix(plane->inversed_t);	
	#endif /* ifdef TEST_H
		*/
}

