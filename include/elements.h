#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "structs.h"

// # Ambient light --------

int	analyze_amblight(char *line, t_data *data);

// # Camera ---------------

int	analyze_camera(char *line, t_data *data);
int	set_coordinates(char *coord_line);
int	set_vector_3d(char *vector_line);
int	set_fov(char *fov_line, t_data *data);
int	validate_range_3d(char **str);
int	validate_numbers_dot(char **str);
int	validate_fov(char *fov_line, t_data *data);
int	normalize_and_set(char **vector_str);

// # Light ---------------

int	analyze_light(char *line, t_data *data);
int	set_brightness(char *bright_line, t_data *data);

// # Sphere --------------

int	analyze_sphere(char *line, t_data *data);

// # Cylinder ------------

int	analyze_cylinder(char *line, t_data *data);

// # Plane ---------------

int	analyze_plane(char *line, t_data *data);

// # Aux ----------------

int	set_range(char *line, int min, int max);
int	set_colors(char *color_line);

#endif
