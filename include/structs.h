/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:35:07 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/20 17:10:33 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*	Struct to save line only */

typedef struct s_parser
{
	int						has_a;
	int						has_c;
	int						has_l;
}							t_parser;

/*	Generic structs to elements (ACL and objects) */

typedef struct s_coords
{
	double					x;
	double					y;
	double					z;
}							t_coords;

typedef struct s_vec3
{
	double					x;
	double					y;
	double					z;
}							t_vec3;

typedef struct s_matrix
{
	int						rows;
	int						cols;
	double					matrix[4][4];
}							t_matrix;

/*	Mandatory elements */

typedef struct s_camera
{
	int						height_v;
	int						width_v;
	double					fov;
	double					pixel_size;
	double					half_height;
	double					half_width;
	double					aspect_ratio;
	t_coords				origin;
	t_vec3					orientation;
	t_vec3					up;
	t_matrix				transform;
	t_matrix				inversed_t;
}							t_camera;

typedef struct s_light
{
	t_coords				position;
	double					brightness;
}							t_light;

typedef struct s_amblight
{
	double					ratio;
	int						color[3];
}							t_amblight;

/*	Objects */

typedef enum e_object_type
{
	SPHERE,
	CYLINDER,
	PLANE
}							t_object_type;

typedef struct s_sphere
{
	double					diameter;
	int						color[3];
	t_coords				position;
}							t_sphere;

typedef struct s_plane
{
	int						color[3];
	double					radius;
	t_coords				position;
	t_vec3					vector;
}							t_plane;

typedef struct s_cylinder
{
	double					max;
	double					min;
	double					height;
	double					diameter;
	int						color[3];
	t_coords				position;
	t_vec3					vector;
}							t_cylinder;

/* Ray and color */
typedef struct s_bhaskara
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	root1;
	double	root2;
	int		status;
}				t_bhaskara;


typedef struct s_color
{
	double					r;
	double					g;
	double					b;
	double					a;
}							t_color;

/*	Struct BVH */

typedef struct s_aabb
{
	t_vec3					min;
	t_vec3					max;
}							t_aabb;

typedef struct s_obj
{
	t_aabb					bbox;
	void					*object;
}							t_obj;

typedef struct s_bvh_node
{
	void					*object;
	t_object_type			type;
	struct s_bvh_node		*left;
	struct s_bvh_node		*right;
	t_aabb					bbox;
}							t_bvh_node;

/*	Struct object, intersection and computations */

typedef struct s_object
{
	t_object_type			type;
	void					*object;
	struct s_object			*next;
}							t_object;

typedef struct s_ray
{
	double					closest_t;
	t_coords				origin;
	t_vec3					direction;
	t_object				*closest_object;
}							t_ray;

typedef struct s_inter
{
	double					t;
	t_vec3					point;
	t_vec3					normal;
	t_object				*object;
}							t_inter;

typedef struct s_inter_list
{
	t_inter					inter;
	struct s_inter_list		*next;
}							t_inter_list;

typedef struct s_comps
{
	double					t;
	int						inside;
	t_coords				point;
	t_coords				over_point;
	t_vec3					eyev;
	t_vec3					normalv;
}							t_comps;

/*	Struct masters */

typedef struct s_data
{
	char					buffer[65535];
	t_parser				parser;
	t_amblight				amblight;
	t_camera				camera;
	t_light					light;
	t_object				*objects;
	t_bvh_node				*bvh_root;
}							t_data;

#endif
