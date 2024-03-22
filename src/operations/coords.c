/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:06 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:37:07 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_coords	set_coords(double x, double y, double z)
{
	return ((t_coords){x, y, z});
}

t_vec3	set_coords_to_vector(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	subtract_coords(t_coords a, t_coords b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}
