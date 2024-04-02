#include "../../../include/test.h"

void	test_ray_hits_sphere(void)
{
	// informações sobre a esfera
	t_sphere	sphere;
	t_ray		ray;
	double		closest_t;
	double		expected_t;
	bool		hit;

	// test #1
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #1 - start\n"RESET);
	sphere.position = set_coords(0, 0, 0);
	sphere.diameter = 2;
	ray.origin = set_coords(0, 0, -5);
	ray.direction = set_vector(0, 0, 1);
	ray.closest_t = INFINITY;
	expected_t = 4.0;
	hit = hit_sphere(&sphere, &ray, &closest_t);
	if (hit)
		check_equal_doubles_p(closest_t, expected_t, "Distância até a interseção");
	else
	 	printf("Falha no teste: Raio não atinge a esfera quando deveria\n");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #1 - end\n\n"RESET);	

	// test #2
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #2 - start\n"RESET);
	sphere.position = set_coords(0, 0, 0);
	sphere.diameter = 2;
	ray.origin = set_coords(0, 1, -5);
	ray.direction = set_vector(0, 0, 1);
	ray.closest_t = INFINITY;
	expected_t = 5.0;
	hit = hit_sphere(&sphere, &ray, &closest_t);
	if (hit)
		check_equal_doubles_p(closest_t, expected_t, "Distância até a interseção");
	else
	 	printf("Falha no teste: Raio não atinge a esfera quando deveria\n");
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #2 - end\n\n"RESET);	
	
	// test #3
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #3 - start\n"RESET);
	sphere.position = set_coords(0, 0, 0);
	sphere.diameter = 2;
	ray.origin = set_coords(0, 2, -5);
	ray.direction = set_vector(0, 0, 1);
	ray.closest_t = INFINITY;
	expected_t = 0.0;
	hit = hit_sphere(&sphere, &ray, &closest_t);
	if (hit)
		check_equal_doubles_p(closest_t, expected_t, "Distância até a interseção");
	else
	 	printf(GREEN"Sucesso no teste:"RESET BOLD" Raio não atinge nestas coordenadas\n"RESET);
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #3 - end\n\n"RESET);	
	
	// test #4
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #4 - start\n"RESET);
	sphere.position = set_coords(0, 0, 0);
	sphere.diameter = 2;
	ray.origin = set_coords(0, 0, 0);
	ray.direction = set_vector(0, 0, 1);
	ray.closest_t = INFINITY;
	expected_t = -1.0;
	hit = hit_sphere(&sphere, &ray, &closest_t);
	if (hit)
		check_equal_doubles_p(closest_t, expected_t, "Distância até a interseção");
	else
	 	printf(GREEN"Falha no teste:"RESET BOLD" Raio não atinge nestas coordenadas\n"RESET);
	printf(F_WHITE"Test #12 - "RESET BOLD"Raio | Teste origem/direção #4 - end\n\n"RESET);	
}

