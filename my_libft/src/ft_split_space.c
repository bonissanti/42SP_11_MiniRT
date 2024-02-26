/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:02:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/07/20 14:45:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	count_words(const char *str)
{
	size_t	count;

	count = 0;
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
	return (count);
}

static char	count_chars(char const *str)
{
	size_t	count;

	count = 0;
	while (*str && !ft_isspace(*str))
	{
		count++;
		str++;
	}
	return (count);
}

static void	copy_words(char **word_list, char const *str)
{
	size_t	len_words;

	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str)
		{
			len_words = count_chars(str);
			*word_list = ft_substr(str, 0, len_words);
			word_list++;
			str += len_words;
		}
		else
			str++;
	}
	*word_list = NULL;
}

char	**ft_split_space(char const *s)
{
	char	**str;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (str == NULL)
		return (NULL);
	copy_words(str, s);
	return (str);
}
