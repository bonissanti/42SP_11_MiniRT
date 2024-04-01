#include "../../../include/test.h"

void	test_set_ray(void)
{
	t_ray ray;
	t_coords origin = set_coords(1, 2, 3);
	t_vec3 direction = set_vector(4, 5, 6);

	ray.origin = origin;
	ray.direction = direction;
	
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção - start\n"RESET);
	compare_double(ray.origin.x, 1, "Comparação x da origem do raio");
	compare_double(ray.origin.y, 2, "Comparação y da origem do raio");
	compare_double(ray.origin.z, 3, "Comparação z da origem do raio");
	compare_double(ray.direction.x, 4, "Comparação x da direção do raio");
	compare_double(ray.direction.y, 5, "Comparação y da direção do raio");
	compare_double(ray.direction.z, 6, "Comparação z da direção do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção - end\n\n"RESET);	
}


void	test_ray_position_x_direction(void)
{
	t_ray		ray;
	t_coords	position;
	t_coords	expected;

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - x #1 - start\n"RESET);
	ray.origin = set_coords(2, 3, 4);
	ray.direction = set_vector(1, 0, 0);
	position = get_intersection_point(ray, 0);
	expected = set_coords(2, 3, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - x #1 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção #2 - start\n"RESET);
	ray.direction = set_vector(1, 0, 0);
	position = get_intersection_point(ray, 1);
	expected = set_coords(3, 3, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - x #2 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - x #3 - start\n"RESET);
	ray.direction = set_vector(1, 0, 0);
	position = get_intersection_point(ray, -1);
	expected = set_coords(1, 3, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - x #3 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - x #4 - start\n"RESET);
	ray.direction = set_vector(1, 0, 0);
	position = get_intersection_point(ray, 2.5);
	expected = set_coords(4.5, 3, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - x #4 - end\n\n"RESET);	
}

void	test_ray_position_y_direction(void)
{
	t_ray		ray;
	t_coords	position;
	t_coords	expected;

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #1 - start\n"RESET);
	ray.origin = set_coords(2, 3, 4);
	ray.direction = set_vector(0, 1, 0);
	position = get_intersection_point(ray, 0);
	expected = set_coords(2, 3, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #1 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #2 - start\n"RESET);
	ray.direction = set_vector(0, 1, 0);
	position = get_intersection_point(ray, 1);
	expected = set_coords(2, 4, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #2 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #3 - start\n"RESET);
	ray.direction = set_vector(0, 1, 0);
	position = get_intersection_point(ray, -1);
	expected = set_coords(2, 2, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #3 - end\n\n"RESET);	


	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #4 - start\n"RESET);
	ray.direction = set_vector(0, 1, 0);
	position = get_intersection_point(ray, 2.5);
	expected = set_coords(2, 5.5, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - y #4 - end\n\n"RESET);	
}

void	test_ray_position_z_direction(void)
{
	t_ray		ray;
	t_coords	position;
	t_coords	expected;

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - z #1 - start\n"RESET);
	ray.origin = set_coords(2, 3, 4);
	ray.direction = set_vector(0, 0, 1);
	position = get_intersection_point(ray, 0);
	expected = set_coords(2, 3, 4);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - z #1 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção #2 - start\n"RESET);
	ray.direction = set_vector(0, 0, 1);
	position = get_intersection_point(ray, 1);
	expected = set_coords(2, 3, 5);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - z #2 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - z #3 - start\n"RESET);
	ray.direction = set_vector(0, 0, 1);
	position = get_intersection_point(ray, -1);
	expected = set_coords(2, 3, 3);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - z #3 - end\n\n"RESET);	

	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - z #4 - start\n"RESET);
	ray.direction = set_vector(0, 0, 1);
	position = get_intersection_point(ray, 2.5);
	expected = set_coords(2, 3, 6.5);
	check_equal_doubles_p(position.x, expected.x, "Posição x do raio");
	check_equal_doubles_p(position.y, expected.y, "Posição y do raio");
	check_equal_doubles_p(position.z, expected.z, "Posição z do raio");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste do ponto de interseção - z #4 - end\n\n"RESET);	
}

void	test_ray_position(void)
{
	test_ray_position_x_direction();
	test_ray_position_y_direction();
	test_ray_position_z_direction();
}
