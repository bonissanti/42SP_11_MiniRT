/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:19:37 by renato            #+#    #+#             */
/*   Updated: 2024/04/22 13:25:43 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color	multiply_color(t_color color, double scalar)
{
	t_color	result;

	result.r = color.r * scalar;
	result.g = color.g * scalar;
	result.b = color.b * scalar;
	result.a = 1;
	return (result);
}

t_color	add_colors(t_color a, t_color b)
{
	t_color	result;

	result.r = a.r + b.r;
	result.g = a.g + b.g;
	result.b = a.b + b.b;
	result.a = 1;
	return (result);
}

t_color	set_to_range_color(t_color color)
{
	t_color	result;

	result.r = fmin(fmax(color.r, 0.0), 1.0);
	result.g = fmin(fmax(color.g, 0.0), 1.0);
	result.b = fmin(fmax(color.b, 0.0), 1.0);
	result.a = 1;
	return (result);
}

t_color	set_color(double color[3])
{
	t_color	result;

	result.r = color[0];
	result.g = color[1];
	result.b = color[2];
	result.a = 1;
	return (result);
}

int	t_color_to_int(t_color color)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (int)(color.r * 255.999);
	green = (int)(color.g * 255.999);
	blue = (int)(color.b * 255.999);
	alpha = (int)(color.a * 255.999);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}
