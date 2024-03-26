#include "../../../include/test.h"

void	test_transform_sphere(void)
{
	t_sphere	sphere;

	sphere.position = set_coords(1.0, 2.0, 3.0);
	sphere.diameter = 2.0;

	t_matrix scale = scaling_matrix(sphere.diameter, sphere.diameter, sphere.diameter);
	t_matrix translate = translation_matrix(sphere.position.x, sphere.position.y, sphere.position.z);
	t_matrix expected = matrix_multiply(&translate, &scale);
	t_matrix result = transform_sphere(sphere.position, sphere.diameter);

	printf(F_WHITE"Test #10 - "RESET BOLD"Sphere | Transformation - start\n"RESET);
	check_equal_matrices(result, expected, "Transformação de esfera");
	printf(F_WHITE"Test #10 - "RESET BOLD"Sphere | Transformation - end\n\n"RESET);	
}
