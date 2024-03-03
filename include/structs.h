#ifndef STRUCTS_H
# define STRUCTS_H

/*	Struct to save line only */

typedef struct s_parser
{ 
    int    		has_A;
    int    		has_C;  
    int    		has_L; 
}               t_parser;

/*	Generic structs to elements (ACL and objects) */

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

/*	Mandatory elements */

typedef struct s_camera
{ 
	int			hview;
	int			wview;
	double		fov;
	t_coords	point;
	t_vec3		vector;
}				t_camera;

typedef struct s_light
{
	t_coords	position;
	double		brightness;
}				t_light;

typedef struct s_amblight
{ 
	double  	ratio; 
   	int    		color[3];
}               t_amblight;

/*	Objects */

typedef struct s_sphere
{ 
	double  	diameter; 
   	int    		color[3];
	t_coords	position;
}               t_sphere;

typedef struct s_plane
{ 
   	int    		color[3];
	t_coords	position;
	t_vec3		vector;
}               t_plane;

typedef struct s_cylinder
{ 
	double		height;
	double		diameter;
   	int    		color[3];
	t_coords	position;
	t_vec3		vector;
}               t_cylinder;

/*	Struct masters */

typedef struct	s_objects
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_plane		plane;
}				t_objects;

typedef struct s_data 
{ 
	char		buffer[4096];
	t_parser	parser;
	t_amblight	amblight;
	t_camera	camera;
	t_light		light;
	t_objects	objects;
} 				t_data;


# endif
