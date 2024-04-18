/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:27:43 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 14:27:44 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "structs.h"

t_ray		ray_for_pixel(t_camera *camera, double x, double y);
bool		hit_cylinder(const t_cylinder *cyl, t_ray ray, double t[2]);
// bool		hit_sphere(const t_sphere *sphere, t_ray ray, t_inter *xs);
bool		hit_sphere(const t_sphere *sphere, t_ray ray, double *t);
bool		hit_plane(t_ray ray, double t[2]);
t_color		trace_ray2(t_data *data, t_ray ray);
t_color		trace_ray(t_data *data, t_ray ray);
t_ray		ray_transform(t_ray ray, t_matrix matrix);
t_vec3		get_intersection_point(t_ray ray, double t);
t_coords	ray_position(t_ray ray, double distance);

#endif
