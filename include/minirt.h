#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <float.h>	// DBL_MAX, DBL_MIN
# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "elements.h"
# include "structs.h"
# include "mlx_utils.h"
# include "bvh.h"
# include "matrix.h"
# include "ray.h"

/* Macros */

# define OK 		0 
# define ERROR 		1
# define EPSILON	0.00001

/* key config */

# define KEY_ESC 65307

// # Init --------------------

void	init_structs(t_data *data);
int		valid_file(char *file, t_data *data);
int		parse_lines(t_data *data);

// # Generic functions -------

t_coords	set_coords(double x, double y, double z);
t_vec3	set_vector(double x, double y, double z);
double	dot_product(t_vec3 a, t_vec3 b);
t_vec3	normalize_vector(t_vec3 value);
t_vec3	cross_vector(t_vec3 a, t_vec3 b);
t_vec3	subtract_vector(t_vec3 a, t_vec3 b);
t_vec3	subtract_coords(t_coords a, t_coords b);

// # Object lists ------------

int		add_objects(t_data *data, void *obj, t_object_type type);
void	free_objects(t_object *objects);

// # Aux ---------------------

void	render_scene(t_data *data, t_mlx *mlx);
int		count_token(char **tokens, int expected_count, const char *msg);
int		print_error(char *msg);
int		is_number(char *coord);
char	*ft_strtok(char *str, const char *delim);
void	free_array(char **array);
double	ft_atod(char *str);
size_t	ft_strxspn(const char *str, const char *set, int mode);

#endif
