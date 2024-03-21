#ifndef MINIRT_H
# define MINIRT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include "bvh.h"
# include "elements.h"
# include "matrix.h"
# include "mlx_utils.h"
# include "ray.h"
# include "structs.h"
# include "intersection.h"
# include "test.h" // for tests
# include <fcntl.h>
# include <math.h>
# include <float.h> // DBL_MAX, DBL_MIN
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

/* Macros */

# define OK 0
# define ERROR 1
# define EPSILON 0.00001
# define NO_REAL_ROOTS 0
# define ONE_REAL_ROOTS 1
# define TWO_REAL_ROOTS 2

/* key config */

# define KEY_ESC 65307

// # Init --------------------

void		init_structs(t_data *data);
void		init_bhask(t_bhaskara *bhask, t_bhaskara *result);
int			valid_file(char *file, t_data *data);
int			parse_lines(t_data *data);

// # Generic functions -------

t_coords	set_coords(double x, double y, double z);
t_vec3		set_vector(double x, double y, double z);
double		dot_product(t_vec3 a, t_vec3 b);
t_vec3		normalize_vector(t_vec3 value);
t_vec3		cross_vector(t_vec3 a, t_vec3 b);
t_vec3		subtract_vector(t_vec3 a, t_vec3 b);
t_vec3		subtract_coords(t_coords a, t_coords b);
void		print_matrix(t_matrix *to_test);
t_coords	add_coords(t_coords a, t_coords b);

// # Object lists ------------

int			add_objects(t_data *data, void *obj, t_object_type type);
void		free_objects(t_object *objects);

// # Aux ---------------------

void		render_scene(t_data *data, t_mlx *mlx);
int			count_token(char **tokens, int expected_count, const char *msg);
int			print_error(char *msg);
int			is_number(char *coord);
char		*ft_strtok(char *str, const char *delim);
void		free_array(char **array);
double		ft_atod(char *str);
size_t		ft_strxspn(const char *str, const char *set, int mode);

// # TESTING -----------------
void	print_objects(t_object *head);
void	traverseBVH(t_bvh_node *node, int depth);

#endif
