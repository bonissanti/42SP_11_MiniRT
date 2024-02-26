#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "structs.h"

// # Ambient light --------

int		analyze_amblight(char *line, t_data *data);
int		set_ambient_ratio(char *ratio_line, t_data *data);
int		set_ambient_colors(char *color_line, t_data *data);

// # Camera ---------------

int		analyze_camera(char *line, t_data *data);
int		set_coordinates(char *coord_line);
int		set_vector_3d(char *vector_line, t_data *data);
int		set_fov(char *fov_line, t_data *data);
int		validate_range_3d(char **str);
int		validate_split(char **str);
int		validate_fov(char *fov_line, t_data *data);
int		normalize_and_set(char **vector_str, t_data *data);

// # Light ---------------

int		analyze_light(char *line, t_data *data);
int		set_brightness(char *bright_line, t_data *data);

// # Sphere --------------

int		analyze_sphere(char *line, t_data *data);

# endif
