/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:41:38 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:41:52 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_all(char **array, size_t count)
{
	while (count > 0)
	{
		count--;
		free(array[count]);
	}
	free(array);
}

static size_t	ft_count_words(char const *str, char delimiter)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str == delimiter && *str)
			str++;
		if (*str)
		{
			count++;
			while (*str != delimiter && *str)
				str++;
		}
	}
	return (count);
}

static char	*ft_get_word(char const *str, size_t *index,
		char delimiter)
{
	size_t	start;
	size_t	length;

	start = *index;
	length = 0;
	while (str[*index] && str[*index] != delimiter)
	{
		(*index)++;
		length++;
	}
	return (ft_substr(str, start, length));
}

static int	ft_fill_array(char **array, char const *str, char delimiter)
{
	size_t	index;
	size_t	word_index;

	index = 0;
	word_index = 0;
	while (str[index])
	{
		while (str[index] == delimiter && str[index])
			index++;
		if (str[index])
		{
			array[word_index] = ft_get_word(str, &index, delimiter);
			if (!array[word_index])
			{
				ft_free_all(array, word_index);
				return (1);
			}
			word_index++;
		}
	}
	return (0);
}

char	**ft_split(char const *str, char delimiter)
{
	char	**array;
	size_t	word_count;

	if (!str)
		return (ft_calloc(1, sizeof(char *)));
	word_count = ft_count_words(str, delimiter);
	array = ft_calloc(word_count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	if (ft_fill_array(array, str, delimiter))
		return (NULL);
	return (array);
}
