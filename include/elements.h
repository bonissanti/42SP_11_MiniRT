#ifndef ELEMENTS_H
# define ELEMENTS_H

# include "minirt.h"

typedef struct s_parser
{ 
    int    		has_A;
    int    		has_C;  
    int    		has_L; 
}               t_parser;
 
typedef struct s_coords
{ 
	double		x; 
	double		y; 
	double		z; 
}				t_coords;
 
typedef struct s_camera
{ 
	double		fov; 
	t_coords	point;
}				t_camera;
 
typedef struct s_amblight
{ 
	double  	ratio; 
   	int    		color[3];
}               t_amblight;
 
# endif
