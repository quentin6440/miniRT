/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:39:08 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:39:58 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	string_len;
	size_t	index;

	if (!s)
		return (NULL);
	string_len = ft_strlen(s);
	if (start >= string_len || len == 0)
		return (ft_strdup(""));
	if (len > string_len - start)
		len = string_len - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	index = 0;
	while (index < len)
	{
		result[index] = s[start + index];
		index++;
	}
	result[index] = '\0';
	return (result);
}
