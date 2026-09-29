/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 22:31:11 by qcyril-a          #+#    #+#             */
/*   Updated: 2025/10/11 14:37:56 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		totsz;
	void	*ptr;

	totsz = nmemb * size;
	ptr = NULL;
	if (!totsz || totsz == 0)
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		((char *)ptr)[0] = 0;
		return (ptr);
	}
	if (nmemb != totsz / size)
		return (NULL);
	ptr = malloc(totsz);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, totsz);
	return (ptr);
}
