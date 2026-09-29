/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:24:13 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:29:01 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_parse_integer(char *str, int *index,
		double *value, int *digits)
{
	while (ft_is_digit(str[*index]))
	{
		*value = *value * 10.0 + (str[*index] - '0');
		if (*value > 1000000.0)
			return (1);
		(*digits)++;
		(*index)++;
	}
	return (0);
}

static void	ft_parse_fraction(char *str, int *index,
		double *value, int *digits)
{
	double	factor;

	if (str[*index] != '.')
		return ;
	(*index)++;
	factor = 0.1;
	while (ft_is_digit(str[*index]))
	{
		*value += (str[*index] - '0') * factor;
		factor *= 0.1;
		(*digits)++;
		(*index)++;
	}
}

int	ft_atof(char *str, double *out)
{
	int		index;
	int		sign;
	int		digits;
	double	value;

	if (!str || !out || !str[0])
		return (1);
	index = 0;
	sign = 1;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	value = 0.0;
	digits = 0;
	if (ft_parse_integer(str, &index, &value, &digits))
		return (1);
	ft_parse_fraction(str, &index, &value, &digits);
	if (!digits || str[index] != '\0')
		return (1);
	*out = value * sign;
	return (0);
}
