#ifndef STRUCTS_H
# define STRUCTS_H

/**
 * Struct: t_parser
 * --------------------
 * Struct to save lines only.
 * 
**/

typedef struct s_parser
{ 
    int    		has_A;
    int    		has_C;  
    int    		has_L; 
}               t_parser;

/**
 * Structs from t_camera
 * --------------------
 * Includes t_coords, t_vec3 and t_camera.
 * 
**/

typedef struct s_coords
{ 
	double		x; 
	double		y; 
	double		z; 
}				t_coords;

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_camera
{ 
	int			hview;
	int			wview;
	double		fov;
	t_coords	point;
	t_vec3		vec_point;
}				t_camera;

/**
 * Structs from amblight
 * --------------------
 * Only one struct. 
 * 
**/

typedef struct s_amblight
{ 
	double  	ratio; 
   	int    		color[3];
}               t_amblight;

/**
 * Struct: t_data
 * --------------------
 * Main struct of the project, all other structs are nested
 * within it.
 * 
**/

typedef struct s_data 
{ 
	char		buffer[4096];
	t_parser	parser;
	t_amblight	amblight;
	t_camera	camera;
} 				t_data;

# endif
