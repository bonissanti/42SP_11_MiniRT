#include "../include/libft.h"

static size_t count_words(char const *str)
{
	size_t count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str)
		{
			count++;
			while (*str && !ft_isspace(*str))
				str++;
		}
	}
	return count;
}

static size_t count_chars(char const *str)
{
	size_t count = 0;
	while (*str && !ft_isspace(*str))
	{
		count++;
		str++;
	}
	return count;
}

static void copy_words(char **word_list, char const *str)
{
	size_t len_words;

	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str)
		{
			len_words = count_chars(str);
			*word_list = malloc(len_words + 1);
			if (*word_list == NULL) return; // Handle malloc failure
			for (size_t i = 0; i < len_words; i++)
			{
				(*word_list)[i] = str[i];
			}
			(*word_list)[len_words] = '\0';
			word_list++;
			str += len_words;
		}
	}
	*word_list = NULL;
}

char **ft_split_space(char const *s)
{
	char **str;
	size_t words;

	if (!s)
		return (NULL);
	words = count_words(s);
	str = malloc(sizeof(char *) * (words + 1));
	if (str == NULL)
	{
		return (NULL);
	}
	copy_words(str, s);
	return (str);
}
