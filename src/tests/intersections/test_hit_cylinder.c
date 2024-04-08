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

void	test_ray_hits_cylinder(void)
{
	t_cylinder	cylinder;
	t_ray		ray;
	double		closest_t[2];
	// double		expected_t[2];
	// bool		hit;


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
	
}

