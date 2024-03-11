#ifndef STRUCTS_H
# define STRUCTS_H

/*	Struct to save line only */

typedef struct s_parser
{
	int			has_a;
	int			has_c;
	int			has_l;
}				t_parser;

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

typedef struct s_matrix
{
	double	matrix[4][4];
}				t_matrix;


/*	Mandatory elements */

typedef struct s_camera
{
	int			height_v;
	int			width_v;
	double		fov;
	double		pixel_size;
	double		half_height;
	double		half_width;
	double		aspect_ratio;
	t_coords	point;
	t_vec3		vector;
	t_vec3		up;
	t_matrix	transform;
	t_matrix	inversed_t;
}				t_camera;

typedef struct s_light
{
	t_coords	position;
	double		brightness;
}				t_light;

typedef struct s_amblight
{
	double		ratio;
	int			color[3];
}				t_amblight;

/*	Objects */

typedef enum e_object_type
{
	SPHERE,
	CYLINDER,
	PLANE
}			t_object_type;

typedef struct s_sphere
{
	double		diameter;
	int			color[3];
	t_coords	position;
}				t_sphere;

typedef struct s_plane
{
	int			color[3];
	double		radius;
	t_coords	position;
	t_vec3		vector;
}				t_plane;

typedef struct s_cylinder
{
	double		max;
	double		min;
	double		height;
	double		diameter;
	int			color[3];
	t_coords	position;
	t_vec3		vector;
}				t_cylinder;

/* Ray and color */

typedef struct	s_ray
{
	t_coords	origin;
	t_vec3		direction;
}				t_ray;

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
	double	a;
}				t_color;

/*	Struct masters */

typedef struct s_object
{
	t_object_type	type;
	void			*object;
	struct s_object	*next;
}					t_object;

/* typedef struct	s_intersections */
/* { */
/* 	double	distance; */
/* 	t_object obj; */
/* 	struct s_intersections *next; */
/* }					t_interesections; */

typedef struct s_data
{
	char		buffer[65535];
	t_parser	parser;
	t_amblight	amblight;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}				t_data;


#endif
