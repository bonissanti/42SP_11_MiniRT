#include "../include/minirt.h"

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
