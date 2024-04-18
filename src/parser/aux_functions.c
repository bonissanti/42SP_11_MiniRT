/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:58 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/18 12:58:57 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * Function: count_token
 * --------------------
 *
 * Counts the number of tokens in an array of strings and compares the count
 * against an expected value. If the count does not match the expected value,
 * a specified message is output to a specified file descriptor (stderr),
 * and the tokens from splitt are freed.
 *
 * @param tokens: The array of strings to be counted.
 * @param expected_count: The expected number of tokens.
 * @param msg: The message to be output if the count does not match
 * the expected value.
 *
 * @return: 0 if the count matches the expected value, 1 otherwise.
 */

inline int	count_token(char **tokens, int expected_count, const char *msg)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	if (count != expected_count)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		free_array(tokens);
		return (1);
	}
	return (0);
}

int	is_number(char *coord)
{
	int	i;
	int	count_dot;

	i = -1;
	count_dot = 0;
	if (coord[0] == '-')
		i++;
	while (coord[++i] != '\0')
	{
		if (coord[i] == '.')
		{
			count_dot++;
			if (count_dot > 1)
				return (ERROR);
		}
		else if (!ft_isdigit(coord[i]))
			return (ERROR);
	}
	return (OK);
}

int	set_coordinates(char *coord_line)
{
	char	**coord_split;

	coord_split = ft_split(coord_line, ',');
	if (count_token(coord_split, 3, "Incorrect number of coordinates, "
			"e.g [-10.0,0,0]\n"))
		return (ERROR);
	if (validate_numbers_dot(coord_split) == ERROR)
	{
		free_array(coord_split);
		return (ERROR);
	}
	free_array(coord_split);
	return (OK);
}

int	set_range(char *line, int min, int max)
{
	double	value;

	if (is_number(line) == ERROR)
		return (ERROR);
	value = ft_atod(line);
	if (value < min || value > max)
		return (ERROR);
	return (OK);
}

int	validate_numbers_dot(char **str)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (is_number(str[i]) == ERROR)
			return (print_error("Invalid number"));
	}
	return (OK);
}
