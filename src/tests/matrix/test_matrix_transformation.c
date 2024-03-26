#include "../../../include/test.h"

void	test_matrix_transformation(void)
{
	t_coords	to;
	t_vec3		up;
	t_camera	camera;
	// t_matrix	expected;

	// test #1
	// to = set_coords(0, 0, -1);
	// up = set_vector(0, 1, 0);
	// camera.origin = set_coords(0, 0, 0);
	// camera.orientation = normalize_vector(subtract_coords(to, camera.origin));
	// set_camera_transform(&camera, up);
	// matrix_identity(&expected);
	// printf(F_WHITE"Test #9 - "RESET BOLD"Matrix | Transformation - start\n"RESET);
	// check_equal_matrices(camera.transform, expected, "Comparação de transformação 1");
	// printf(F_WHITE"Test #9 - "RESET BOLD"Matrix | Transformation - end\n\n"RESET);	

	// test #2
	to = set_coords(0, 0, 1);
	up = set_vector(0, 1, 0);
	camera.origin = set_coords(0, 0, 0);
	camera.orientation = normalize_vector(subtract_coords(to, camera.origin));
	set_camera_transform(&camera, up);
	printf(F_WHITE"Test #8 - "RESET BOLD"Matrix | Transformation + escala - start\n"RESET);
	// print_matrix(camera.transform);
	check_equal_matrices(camera.transform, scaling_matrix(-1, 1, -1), "Comparação de transformação 2");
	printf(F_WHITE"Test #8 - "RESET BOLD"Matrix | Transformation + escala - end\n\n"RESET);	
}

