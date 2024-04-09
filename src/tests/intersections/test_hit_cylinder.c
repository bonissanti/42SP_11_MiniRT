#include "../../../include/test.h"


void	no_intersection(t_cylinder cyl, t_ray ray, double closest_t[2])
{
	bool	hit;

	hit = hit_cylinder(&cyl, ray, closest_t);
	if (hit == false)
	 	printf(GREEN"Sucesso no teste: "RESET L_GRAY"Não deve haver interseção nessa configuração\n"RESET);
	else
	 	printf(RED"Falha no teste: "RESET L_GRAY"Raio atinge a esfera quando não deveria\n"RESET);
}

void	have_intersection(t_cylinder cyl, t_ray ray, double closest_t[2], double expected_t[2])
{
	bool	hit;

	hit = hit_cylinder(&cyl, ray, closest_t);
	if (hit == true)
	{
		check_equal_doubles_p(closest_t[0], expected_t[0], "Distância até a interseção");
		check_equal_doubles_p(closest_t[1], expected_t[1], "Distância até a interseção");
	}
	else
	 	printf("Falha no teste: Raio não atinge a esfera quando deveria\n");
}

void	test_ray_hits_cylinder(void)
{
	t_cylinder	cylinder;
	t_ray		ray;
	double		closest_t[2];
	double		expected_t[2];
	// bool		hit;

	memset(&cylinder, 0, sizeof(t_cylinder));
	// test #1 - No intersection
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio Cilindro | Teste origem/direção #1 - start\n"RESET);
	ray.origin = set_coords(1, 0, 0);
	ray.direction = set_vector(0, 1, 0);
	no_intersection(cylinder, ray, closest_t);
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio | Teste origem/direção #1 - end\n\n"RESET);	
	
	// test #2 - No intersection
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio Cilindro | Teste origem/direção #2 - start\n"RESET);
	ray.origin = set_coords(0, 0, 0);
	ray.direction = set_vector(0, 1, 0);
	no_intersection(cylinder, ray, closest_t);
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio | Teste origem/direção #2 - end\n\n"RESET);	
	
	// test #3 - No intersection
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio Cilindro | Teste origem/direção #3 - start\n"RESET);
	ray.origin = set_coords(0, 0, -5);
	ray.direction = set_vector(1, 1, 1);
	no_intersection(cylinder, ray, closest_t);
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio | Teste origem/direção #3 - end\n\n"RESET);	
	
	// test #4 - Ray hits cylinder
	expected_t[0] = 5.0;
	expected_t[1] = 5.0;
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio Cilindro | Teste origem/direção #4 - start\n"RESET);
	ray.origin = set_coords(1, 0, -5);
	ray.direction = set_vector(0, 0, 1);
	have_intersection(cylinder, ray, closest_t, expected_t);
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio | Teste origem/direção #4 - end\n\n"RESET);	

	// test #5 - Ray hits cylinder
	expected_t[0] = 4.0;
	expected_t[1] = 6.0;
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio Cilindro | Teste origem/direção #5 - start\n"RESET);
	ray.origin = set_coords(0, 0, -5);
	ray.direction = set_vector(0, 0, 1);
	have_intersection(cylinder, ray, closest_t, expected_t);
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio | Teste origem/direção #5 - end\n\n"RESET);
	
	// test #6 - Ray hits cylinder
	expected_t[0] = 6.80798;
	expected_t[1] = 7.08872;
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio Cilindro | Teste origem/direção #6 - start\n"RESET);
	ray.origin = set_coords(0.5, 0, -5);
	ray.direction = normalize_vector(set_vector(0.1, 1, 1));
	have_intersection(cylinder, ray, closest_t, expected_t);
	printf(F_WHITE"Test #13 - "RESET BOLD"Raio | Teste origem/direção #6 - end\n\n"RESET);
}

