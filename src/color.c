/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by quentin           #+#    #+#             */
/*   Updated: 2026/09/28 17:51:39 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec3	ft_color_add(t_vec3 a, t_vec3 b)
{
	return (vec_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	ft_color_mul(t_vec3 a, t_vec3 b)
{
	return (vec_new(a.x * b.x / 255.0,
			a.y * b.y / 255.0,
			a.z * b.z / 255.0));
}

t_vec3	ft_color_scale(t_vec3 color, double ratio)
{
	return (vec_new(color.x * ratio,
			color.y * ratio,
			color.z * ratio));
}

double	ft_color_clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
