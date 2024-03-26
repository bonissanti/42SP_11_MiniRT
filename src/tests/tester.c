#include "../../../include/test.h"

int	main(void)
{
	test_validation();
	test_analyze_amblight();
	test_identity_matrix();
	test_matrix_transformation();
	test_ray_for_pixel();
	test_transform_sphere();
	test_determinant();
	test_cofactor_matrix();
	test_calculate_minor();
	return (0);
}
