#include "../../../include/test.h"

int	main(void)
{
	test_validation();
	test_analyze_amblight();
	test_camera();
	test_light();
	test_sphere();
	test_identity_matrix();
	test_cylinder();
	// test_matrix_transformation();
	test_ray_for_pixel();
	test_transform_sphere();
	test_determinant();
	test_cofactor_matrix();
	test_calculate_minor();
	test_set_ray();
	test_ray_hits_sphere();
	test_ray_position();
	test_ray_hits_cylinder();
	test_ray_hits_plane();
	test_intersection_obj();
	test_atan();
	return (0);
}
