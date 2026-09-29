/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:16:40 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:16:48 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_str_to_float(char *str, double *out)
{
	return (ft_atof(str, out));
}

int	ft_str_to_color(char *str, t_vec3 *color)
{
	char	**parts;
	int		red;
	int		green;
	int		blue;

	if (!str || !color)
		return (1);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (ft_free_tab(parts), 1);
	if (ft_atoi_strict(parts[0], &red) != 0
		|| ft_atoi_strict(parts[1], &green) != 0
		|| ft_atoi_strict(parts[2], &blue) != 0)
		return (ft_free_tab(parts), 1);
	ft_free_tab(parts);
	color->x = (double)red;
	color->y = (double)green;
	color->z = (double)blue;
	return (0);
}

int	ft_str_to_vec3(char *str, t_vec3 *vec, int is_dir)
{
	char	**parts;

	if (!str || !vec)
		return (1);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (ft_free_tab(parts), 1);
	if (ft_str_to_float(parts[0], &vec->x) != 0
		|| ft_str_to_float(parts[1], &vec->y) != 0
		|| ft_str_to_float(parts[2], &vec->z) != 0)
		return (ft_free_tab(parts), 1);
	ft_free_tab(parts);
	if (is_dir)
	{
		if (vec->x < -1.0 || vec->x > 1.0
			|| vec->y < -1.0 || vec->y > 1.0
			|| vec->z < -1.0 || vec->z > 1.0)
			return (1);
		if (vec->x == 0.0 && vec->y == 0.0 && vec->z == 0.0)
			return (1);
	}
	return (0);
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
