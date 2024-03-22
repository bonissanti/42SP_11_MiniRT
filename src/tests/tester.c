#include "../../include/test.h"

int	main(void)
{
	test_validation();
	test_analyze_amblight();
	test_identity_matrix();
	test_matrix_transformation();
	test_ray_for_pixel();
	return (0);
}
