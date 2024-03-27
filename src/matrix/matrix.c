/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:37:17 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/26 11:55:57 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	matrix_identity(t_matrix *mat)
{
	int	y;
	int	x;

	y = -1;
	mat->rows = 4;
	mat->cols = 4;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			if (y == x)
				mat->matrix[y][x] = 1.0;
			else
			 	mat->matrix[y][x] = 0.0;
		}
	}
# ifdef TEST
	printf("identity matrix\n");
	print_matrix(*mat);
# endif
}

//TODO: Talvez essa função esteja inútil aqui, já que armazeno na stack.
t_matrix	*create_matrix(void)
{
	t_matrix	*transform;

	transform = malloc(sizeof(t_matrix));
	if (!transform)
		return (NULL);
	matrix_identity(transform);
	return (transform);
}

void	matrix_free(t_matrix *matrix)
{
	if (matrix)
		free(matrix);
}
