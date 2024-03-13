/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:36:58 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:36:59 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/**
 * Function: ft_strxspn
 * --------------------
 * Custom implementation that combines the functionality of the C library 
 * functions strspn and strcspn based on the specified mode. 
 * It operates in two modes:
 * Mode 0 (strspn mode): Returns the length of the initial segment of 'str' 
 * which consists solely of characters found in 'set'. 
 * Example: For str = "hello" and set = "he", it returns 2.
 * Mode 1 (strcspn mode): Returns the length of the initial segment of 'str' 
 * which consists solely of characters not found in 'set'.
 * Example: For str = "hello" and set = "world", it returns 0.
 *
 * @param str: The input string to be searched.
 * @param set: The set of characters to be used for comparison, 
 * depending on the mode.
 * @param mode: Determines the function mode; 0 for strspn mode, 1 for 
 * strcspn mode.
 *
 * @return: The length of the initial segment of 'str' based on the selected 
 * mode.
 */

size_t	ft_strxspn(const char *str, const char *set, int mode)
{
	const char *ptr;
	const char *search;
	size_t 		count;

	count = 0;
	ptr = str;
	while (*ptr)
	{
		search = set;
		while (*search)
		{
			if (*ptr == *search)
				break ;
			search++;
		}
		if ((mode == 0 && !*search) || (mode == 1 && *search))
			return (count);
		ptr++;
		count++;
	}
	return (count);
}

/**
 * Function: ft_strtok
 * --------------------
 * Custom implementation of the strtok function, which is used to tokenize a string 
 * into sequences separated by characters found in the delimiter string. 
 * It maintains a static pointer to keep track of the current position in 
 * the string, allowing subsequent calls with a NULL pointer for 'str' to 
 * continue tokenizing the same string.
 * 
 * @param str: The input string to be tokenized.
 * @param delim: The delimiter string used to separate the tokens.
 * 
 * @return: A pointer to the next token found in the string, or NULL if no more.
 */

char	*ft_strtok(char *str, const char *delim)
{
	static char	*line;

	if (str)
		line = str;
	else if (!line)
		return (NULL);
	str = line + ft_strxspn(line, delim, 0);
	if (!*str)
		return (line = NULL);
	line = str + ft_strxspn(str, delim, 1);
	if (*line)
		*line++ = '\0';
	else
		line = NULL;
	return (str);
}

/**
 * Function: ft_atod
 * --------------------
 * Custom implementation of the atof function, which is used to convert a string
 * to a double-precision floating-point number. It handles both positive and 
 * negative numbers, as well as decimal numbers.
 * 
 * This function works in two steps:
 * 1. It reads the integer part of the number by iterating through the string
 * and converting each character to its corresponding integer value.
 * 
 * 2. If a decimal point is found, it reads the fractional part of the number
 * by iterating through the string and converting each character to its
 * corresponding integer value, while also keeping track of the power of 10
 * to divide the result by the correct amount.
 *  
 * @param str: The input string to be converted to a double.
 *
 * @return: The double value of the input string. 
 */

double	ft_atod(char *str)
{
	double	result;
	double	power;
	int		sign;

	result = 0.0;
	power = 1.0;
	sign = 1;
	
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	if (*str == '.')
	{
		str++;
		while ((*str) && (*str >= '0' || *str <= '9'))
		{
			result = result * 10 + (*str - '0');
			power *= 10;
			str++;
		}
	}
	return (sign * result / power);
}

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
	char **coord_split;
	
	coord_split = ft_split(coord_line, ',');
	if (count_token(coord_split, 3, "Incorrect number of coordinates, e.g [-10.0,0,0]\n"))
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


static int	validate_colors(char **color_str)
{
	int	i;
	int	color;

	i = -1;
	while (++i < 3)
	{
		color = ft_atoi(color_str[i]);
		if (color < 0 || color > 255)
			return (print_error("[A] Color out of range [0, 255]"));
	}
	return (OK);
}

int	set_colors(char *color_line)
{
	char 	**color_split;

	color_split = ft_split(color_line, ',');
	if (count_token(color_split, 3, "[A] Incorrect number of RGB componentes\n"))
		return (ERROR);
	if (validate_colors(color_split) != 0)
	{
		free_array(color_split);
		return (ERROR);
	}
	free_array(color_split); 
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

