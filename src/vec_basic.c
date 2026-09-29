/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:34:32 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 17:53:05 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.h"

t_vec3	vec_new(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec_scale(t_vec3 v, double factor)
{
	return ((t_vec3){v.x * factor, v.y * factor, v.z * factor});
}
