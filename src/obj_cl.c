/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by quentin           #+#    #+#             */
/*   Updated: 2026/09/28 17:52:19 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	ft_hit_cylinder(t_obj *obj, t_ray ray)
{
	double	t_side;
	double	t_caps;

	t_side = ft_hit_cylinder_side(obj, ray);
	t_caps = ft_hit_cylinder_caps(obj, ray, NULL);
	if (t_side > EPSILON && t_caps > EPSILON)
	{
		if (t_side < t_caps)
			return (t_side);
		return (t_caps);
	}
	if (t_side > EPSILON)
		return (t_side);
	if (t_caps > EPSILON)
		return (t_caps);
	return (-1.0);
}
