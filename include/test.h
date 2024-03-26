# ifndef TEST_H
#define TEST_H

# include <assert.h>
# include "minirt.h"

# define RED	"\x1b[91m" 
# define GREEN	"\x1b[92m"
# define F_WHITE "\x1b[37m"
# define L_GRAY	"\x1b[90m"
# define BOLD	"\x1b[1m"
# define RESET	"\x1b[0m"

void	test_validation(void);
void	test_analyze_amblight(void);
void	test_ray_for_pixel(void);
void	test_identity_matrix(void);
void	test_matrix_transformation(void);
void	test_transform_sphere(void);
void	test_identity_matrix(void);
void	test_determinant(void);
void	test_cofactor_matrix(void);
void 	test_calculate_minor(void);

void	check_equal_coords(t_coords *result, t_coords *expected);
void	check_equal_matrices(t_matrix result, t_matrix expected, const char *testName);
void	check_equal_doubles_p(double a, double b, const char *testName);

# endif
