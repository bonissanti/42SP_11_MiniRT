#include "../../../include/test.h"

static void	check_intersection(t_ray ray, double closest_t[2], int mode)
{
	bool	hit;
	double	expected_t;

	expected_t = 1.0;
	hit = hit_plane(ray, closest_t);

	// mode 0: Checks if wrong intersections happen
	if (mode == 0) 
	{
		if (hit == false)
	 		printf(GREEN"Sucesso no teste: "RESET L_GRAY"Não deve haver interseção nessa configuração\n"RESET);
		else
	 		printf(RED"Falha no teste: "RESET L_GRAY"Raio atinge a esfera quando não deveria\n"RESET);
	}
		
	// mode 1: Checks if the correct planned intersections happen
	if (mode == 1)
	{
		if (hit == true)
			check_equal_doubles_p(closest_t[0], expected_t, "Distância até a interseção");
		else
		 	printf("Falha no teste: Raio não atinge a esfera quando deveria\n");
	}
}


void	test_ray_hits_plane(void)
{
	t_ray		ray;
	double		closest_t[2];
	// double		expected_t[2];

	printf(F_WHITE"Test #14 - "RESET BOLD"Raio Plano | Teste raio paralelo #1 - start\n"RESET);
	ray.origin = set_coords(0, 10, 0);
	ray.direction = set_vector(0, 0, 1);
	check_intersection(ray, closest_t, 0);
	printf(F_WHITE"Test #14 - "RESET BOLD"Raio | Teste raio paralelo #1 - end\n\n"RESET);	

	printf(F_WHITE"Test #14 - "RESET BOLD"Raio Plano | Teste raio coplanar #2 - start\n"RESET);
	ray.origin = set_coords(0, 0, 0);
	ray.direction = set_vector(0, 0, 1);
	check_intersection(ray, closest_t, 0);
	printf(F_WHITE"Test #14 - "RESET BOLD"Raio | Teste raio coplanar #2 - end\n\n"RESET);	

	printf(F_WHITE"Test #14 - "RESET BOLD"Raio Plano | Teste raio acima #2 - start\n"RESET);
	ray.origin = set_coords(0, 1, 0);
	ray.direction = set_vector(0, -1, 0);
	check_intersection(ray, closest_t, 1);
	printf(F_WHITE"Test #14 - "RESET BOLD"Raio | Teste raio acima #2 - end\n\n"RESET);	

	printf(F_WHITE"Test #14 - "RESET BOLD"Raio Plano | Teste raio abaixo #2 - start\n"RESET);
	ray.origin = set_coords(0, -1, 0);
	ray.direction = set_vector(0, 1, 0);
	check_intersection(ray, closest_t, 1);
	printf(F_WHITE"Test #14 - "RESET BOLD"Raio | Teste raio abaixo #2 - end\n\n"RESET);	


}


