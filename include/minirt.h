/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:06:35 by rseelaen          #+#    #+#             */
/*   Updated: 2024/04/23 12:17:12 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include "bvh.h"
# include "elements.h"
# include "intersection.h"
# include "matrix.h"
# include "mlx_utils.h"
# include "ray.h"
# include "structs.h"
# include "test.h" // for tests
# include <fcntl.h>
# include <float.h> // DBL_MAX, DBL_MIN
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* Macros */

# define OK 0
# define ERROR 1
# define EPSILON 0.00001
# define NO_REAL_ROOTS 0
# define ONE_REAL_ROOTS 1
# define TWO_REAL_ROOTS 2
# define SPECULAR 0.9
# define DIFFUSE 0.9
# define SHININESS 200

/* key config */

# define KEY_ESC 65307

// # Init --------------------

void		init_structs(t_data *data);
void		init_bhask(t_bhaskara *bhask, t_bhaskara *result);
int			valid_file(char *file, t_data *data);
int			parse_lines(t_data *data);

// # Generic functions -------

bool		compare_vectors(t_vec3 result, t_vec3 expected);
bool		check_equal_doubles(double a, double b);
t_coords	set_coords(double x, double y, double z);
t_vec3		set_up(t_vec3 orientation);
t_vec3		set_vector(double x, double y, double z);
t_vec3		set_coords_to_vector(double x, double y, double z);
double		dot_product(t_vec3 a, t_vec3 b);
t_vec3		normalize_vector(t_vec3 value);
t_vec3		cross_vector(t_vec3 a, t_vec3 b);
t_vec3		matrix_multiply_vector(const t_matrix m, const t_vec3 *point);
t_vec3		subtract_vector(t_vec3 a, t_vec3 b);
t_vec3		subtract_coords(t_coords a, t_coords b);
void		print_matrix(t_matrix to_test);
t_coords	add_tuple(t_coords a, t_coords b);
t_coords	multiply_tuple(t_coords a, double scalar);
t_coords	subtract_tuple(t_coords a, t_coords b);
double		vector_length(t_vec3 v);
t_coords	multiply_vector(t_coords v, double scalar);

// # Object lists ------------

int			add_objects(t_data *data, void *obj, t_object_type type);
void		free_objects(t_object *objects);
void    	add_to_list(t_object *cur, double t, t_inter_list **inter_list);

// # Aux ---------------------

void		render_scene(t_data *data, t_mlx *mlx);
int			count_token(char **tokens, int expected_count, const char *msg);
int			print_error(char *msg);
int			is_number(char *coord);
char		*ft_strtok(char *str, const char *delim);
void		free_array(char **array);
double		ft_atod(char *str);
size_t		ft_strxspn(const char *str, const char *set, int mode);

// # Render ------------------

t_geo_u		get_geo(t_object *object);
t_vec3		sphere_normal(t_vec3 point, t_sphere *sphere);
t_vec3		plane_normal(t_vec3 point, t_plane *plane);
t_vec3		cylinder_normal(t_vec3 point, t_cylinder *cy);
t_vec3		get_normal(t_object *obj, t_vec3 point);

// # Color -------------------

t_color	    multiply_color(t_color color, double scalar);
t_color 	add_colors(t_color a, t_color b);
t_color 	set_to_range_color(t_color color);
t_color 	set_color(double color[3]);
int	        t_color_to_int(t_color color);

// # TESTING -----------------
void		print_objects(t_object *head);
void		traverseBVH(t_bvh_node *node, int depth);

#endif
