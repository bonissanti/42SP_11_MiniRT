/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:34:58 by brunrodr          #+#    #+#             */
/*   Updated: 2024/03/12 15:46:20 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"


int	file_extension(char *file, char *ext)
{
	char	*ptr;
	
	ptr = ft_strrchr(file, '.'); // add libft
	if (!ptr || ptr == file)
	{
		ft_putstr_fd("Error\nFile has no extension\n", 2);
		return (ERROR);
	}
	if (strcmp(ptr, ext) != 0) // add libft
	{
		ft_putstr_fd("Error\nFile must have .rt extension\n", 2);
		return (ERROR);
	}
	return (OK);
}

int	valid_file(char *file, t_data *data)
{
	int	fd;
	int	bytes_read;

	fd = open(file, O_RDONLY);
	if (fd < -1)
		return (print_error("File not found\n"));
	bytes_read = read(fd, data->buffer, 65535);
    if (bytes_read <= 0)
    {
		close(fd);
        return (print_error("File is empty or could not be read"));
    }
	data->buffer[bytes_read] = '\0';
	if (file_extension(file, ".rt"))
	{
		close(fd);
		return (ERROR);
	}		
	close(fd);
	return (OK);
}

/**
 * Function: analyze_line
 * --------------------
 * Analyzes each line of the input data to ensure specific conditions are met.
 *
 * This function checks the first character of each line to increment counters
 * for 'A', 'C', and 'L' characters within a 'parser' structure inside 'data'.
 * These characters are essential for the validity of the input data, with the
 * requirement that exactly one of each must be present in the entire input.
 * If the input does not meet this condition, the function outputs an error 
 * message to stderr and terminates the program.
 * 
 * Additionally, if a line starts with 'A', 'C' or 'L', it calls the appropriate
 * function to perform further analysis on the remainder of the line.
 *
 * @param data: A pointer to the main data structure.
 * 
 * @return: 0 if the parsing was successful.
 */

int	analyze_line(char *line, t_data *data)
{
	data->parser.has_a += (line[0] == 'A');
	data->parser.has_c += (line[0] == 'C');
	data->parser.has_l += (line[0] == 'L');

	if (line[0] == 'A')
		if (analyze_amblight(line + 1, data) != 0)
			exit (1);
	if (line[0] == 'C')
		if (analyze_camera(line + 1, data) != 0)
			exit (1);
	if (line[0] == 'L')
		if (analyze_light(line + 1, data) != 0)
			exit (1);
	if (line[0] == 's' && line[1] == 'p')
		if (analyze_sphere(line + 2, data) != 0)
			exit (1);
	if (line[0] == 'p' && line[1] == 'l')
		if (analyze_plane(line + 2, data) != 0)
			exit (1);
	if (line[0] == 'c' && line[1] == 'y')
		if (analyze_cylinder(line + 2, data) != 0)
			exit (1);
	return (OK);
}

/**
 * Function: parse_lines
 * --------------------
 * Parses the contents of a buffer into individual lines and analyzes each line.
 *
 * This function takes a buffer that contains the contents of a file and splits 
 * it into individual lines using the newline character ('\n') as a delimiter.
 * Each line is then passed to the function 'analyze_line' for further processing. 
 *
 * @param data: A pointer to the main data structure.
 * 
 * @return: 0 if the parsing was successful.
 */

int	parse_lines(t_data *data)
{
	char	*line;
	char 	*buffer;

	buffer = data->buffer;
	line = ft_strtok(buffer, "\n");
	while (line)
	{
		analyze_line(line, data);
		line = ft_strtok(NULL, "\n");
	}
	if (data->parser.has_a != 1 || data->parser.has_c != 1 || data->parser.has_l != 1)
	{
		ft_putstr_fd("Error\nInvalid number of A, C, or L characters\n", 2);
		return (ERROR);
	}
	return (OK);
}


