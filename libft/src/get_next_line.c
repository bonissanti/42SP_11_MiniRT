/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:18:24 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:42:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char		*read_lines(int fd, char *current_line);
static char	find_breakline(char *str);
static char	*get_line(char *str);
static char	*get_remaining(char *str);

char	*get_next_line(int fd)
{
	static char	*line;
	char		*current_line;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	line = read_lines(fd, line);
	if (!gnl_strlen(line))
		return (NULL);
	current_line = get_line(line);
	if (!current_line)
		return (NULL);
	line = get_remaining(line);
	return (current_line);
}

char	*read_lines(int fd, char *current_line)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!find_breakline(current_line))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		current_line = gnl_strjoin(current_line, buffer);
		if (!current_line)
			return (NULL);
	}
	free(buffer);
	return (current_line);
}

static char	find_breakline(char *str)
{
	char	*p;

	p = str;
	if (str == NULL)
		return (0);
	while (*p != '\0')
	{
		if (*p == '\n')
			return (1);
		p++;
	}
	return (0);
}

static char	*get_line(char *str)
{
	char	*p;
	char	*line;
	char	*p_line;

	p = str;
	while (*p != '\n' && *p != '\0')
		p++;
	if (*p == '\n')
		p++;
	line = (char *)malloc(sizeof(char) * (p - str) + 1);
	if (!line)
		return (NULL);
	p_line = line;
	while (*str != '\n' && *str != '\0')
		*p_line++ = *str++;
	if (*str == '\n')
		*p_line++ = *str++;
	*p_line = '\0';
	return (line);
}

static char	*get_remaining(char *str)
{
	char	*p;
	char	*remaining;
	char	*save_position;

	p = str;
	save_position = str;
	while (*p != '\n' && *p != '\0')
		p++;
	if (*p == '\n' && *(p + 1) == '\0')
	{
		free(save_position);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * (gnl_strlen(p) + 1));
	p = remaining;
	while (*str != '\n' && *str != '\0')
		str++;
	if (*str == '\n')
		str++;
	while (*str != '\0')
		*p++ = *str++;
	*p = '\0';
	free(save_position);
	return (remaining);
}
