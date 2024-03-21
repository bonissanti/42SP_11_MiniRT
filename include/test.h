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

# endif
