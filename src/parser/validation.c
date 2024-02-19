#include "../include/minirt.h"

int	file_extension(char *file, char *ext)
{
	char	*ptr;

	ptr = strrchr(file, '.'); // add libft
	if (!ptr || ptr == file)
	{
		ft_putstr_fd("Error\nFile has no extension\n", 2);
		return (1);
	}
	if (strcmp(ptr, ext) != 0) // add libft
	{
		ft_putstr_fd("Error\nFile must have .rt extension\n", 2);
		return (1);
	}
	return (0);
}

int	valid_file(char *file, t_data *data)
{
	int	fd;
	int	bytes_read;

	fd = open(file, O_RDONLY);
	if (fd < -1)
	{
		ft_putstr_fd("Error\nFile not found\n", 2);
		return (1);
	}
	bytes_read = read(fd, data->buffer, 4095);
    if (bytes_read <= -1)
    {
        ft_putstr_fd("Error\nFile is empty or could not be read\n", 2);
		close(fd);
        return (1);
    }
	data->buffer[bytes_read] = '\0';
	if (file_extension(file, ".rt"))
	{
		close(fd);
		return (1);
	}		
	// printf("%s\n", data->buffer); // debug
	close(fd);
	return (0);
}

// int	count_identifiers(char *line, t_parser *parser)
// {
// 	return (parser.has_A == 1 && parser->has_C == 1 && parser->has_L == 1);
// }

int	analyze_line(char *line, t_parser *parser)
{
	parser->has_A += (line[0] == 'A');
	parser->has_C += (line[0] == 'C');
	parser->has_L += (line[0] == 'L');
	if (line[0] == 'A')
		analyze_amblight(line + 1);	
	return (0);
}

int	parse_lines(t_data *data)
{
	char	*line;
	char 	*buffer;
	t_parser	parser;

	memset(&parser, 0, sizeof(parser));
	buffer = data->buffer;
	line = ft_strtok(buffer, "\n");
	while (line)
	{
		analyze_line(line, &parser);
		line = ft_strtok(NULL, "\n");
	}
	if (parser.has_A != 1 || parser.has_C != 1 || parser.has_L != 1)
	{
		ft_putstr_fd("Error\nMap must contain at least one A, C and L\n", 2);
		return (1);
	}
	return (0);
}