#include "../../include/test.h"

void	check_equal_coords(t_coords *result, t_coords *expected)
{
	if (fabs(result->x - expected->x) > EPSILON) 
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, "Comparação de x", expected->x, result->x);
	else if (fabs(result->y - expected->y) > EPSILON)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, "Comparação de y", expected->y, result->y);
	else if (fabs(result->z - expected->z) > EPSILON)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, "Comparação de z", expected->z, result->z);
	else
		printf(GREEN"Sucesso no teste: "RESET L_GRAY"X esperado: %f vs. resultado: %f | Y esperado: %f vs. resultado: %f | Z esperado: %f vs. resultado %f \n"RESET, expected->x, result->x, expected->y, result->y, expected->z, result->z);
}

void	check_equal_vector(t_vec3 *result, t_vec3 *expected)
{
	if (fabs(result->x - expected->x) > EPSILON)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, "Comparação de x", expected->x, result->x);
	else if (fabs(result->y - expected->y) > EPSILON)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, "Comparação de y", expected->y, result->y);
	else if (fabs(result->z - expected->z) > EPSILON)
		printf(RED"Falha no teste: "RESET L_GRAY"'%s': Valor esperado %f, mas foi %f\n"BOLD, "Comparação de z", expected->z, result->z);
	else
		printf(GREEN"Sucesso no teste: "RESET L_GRAY"X esperado: %f vs. resultado: %f | Y esperado: %f vs. resultado: %f | Z esperado: %f vs. resultado %f \n"RESET, expected->x, result->x, expected->y, result->y, expected->z, result->z);
}

t_camera	set_camera_2(double fov, int hsize, int vsize)
{
	t_camera	camera;

	ft_memset(&camera, 0, sizeof(t_camera));
	camera.fov = fov;
	camera.height_v = hsize;
	camera.width_v = vsize;
	camera.half_width = tan(fov / 2);
	camera.half_height = camera.half_width * (double)vsize / (double)hsize;
	camera.pixel_size = (camera.half_width * 2) / (double)hsize;
	return (camera);
}

void	test_ray_for_pixel(void)
{
	t_camera camera;
	t_ray ray;

	// Configura a camera para obter o resultado
	camera = set_camera_2(M_PI / 2, 201, 101);
	matrix_identity(&camera.transform);
	matrix_identity(&camera.inversed_t);
	camera.origin = set_coords(0, 0, 0);
	t_ray result = ray_for_pixel(&camera, 100, 50);

	// Configura o a estrutura ray para obter o esperado
	ray.origin = camera.origin;
	ray.direction = set_vector(0, 0, -1);


	// Compara os resultados das coordenadas - test #1 ray for pixel
	printf(F_WHITE"Test #8 - "RESET BOLD"Render | Ray for pixel 1 - start\n"RESET);
	check_equal_coords(&result.origin, &ray.origin);
	check_equal_vector(&result.direction, &ray.direction);
	printf(F_WHITE"Test #8 - "RESET BOLD"Render | Ray for pixel 1 - end\n\n"RESET);	

	// Test #2 ray for pixel
	ray.direction = set_vector(0.66519, 0.33259, -0.66851);
	result = ray_for_pixel(&camera, 0, 0);
	printf(F_WHITE"Test #8 - "RESET BOLD"Render | Ray for pixel 2 - start\n"RESET);
	check_equal_coords(&result.origin, &ray.origin);
	check_equal_vector(&result.direction, &ray.direction);
	printf(F_WHITE"Test #8 - "RESET BOLD"Render | Ray for pixel 2 - end\n\n"RESET);	

}
