/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:25:12 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:29:03 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi_strict(char *str, int *out)
{
	int		index;
	long	value;

	if (!str || !out || !str[0])
		return (1);
	index = 0;
	value = 0;
	if (str[index] == '+')
		index++;
	if (!str[index])
		return (1);
	while (ft_is_digit(str[index]))
	{
		value = value * 10 + (str[index] - '0');
		if (value > 255)
			return (1);
		index++;
	}
	if (str[index] != '\0')
		return (1);
	*out = (int)value;
	return (0);
}
