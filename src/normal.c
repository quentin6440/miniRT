/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:58:31 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:58:32 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_vec3	ft_sphere_normal(t_hit hit)
{
	t_vec3	normal;

	normal = vec_sub(hit.point, hit.obj->pos);
	return (vec_normalize(normal));
}

static t_vec3	ft_plane_normal(t_hit hit)
{
	return (vec_normalize(hit.obj->dir));
}

static t_vec3	ft_cylinder_normal(t_hit hit)
{
	t_vec3	v;
	t_vec3	axis;
	t_vec3	normal;
	double	projection;
	double	half_height;

	v = vec_sub(hit.point, hit.obj->pos);
	axis = vec_normalize(hit.obj->dir);
	projection = vec_dot(v, axis);
	half_height = hit.obj->height / 2.0;
	if (fabs(projection - half_height) < EPSILON)
		return (axis);
	if (fabs(projection + half_height) < EPSILON)
		return (vec_scale(axis, -1.0));
	normal = vec_sub(v, vec_scale(axis, projection));
	return (vec_normalize(normal));
}

t_vec3	ft_get_normal(t_hit hit)
{
	if (!hit.valid || !hit.obj)
		return (vec_new(0.0, 0.0, 0.0));
	if (hit.obj->type == SPHERE)
		return (ft_sphere_normal(hit));
	if (hit.obj->type == PLANE)
		return (ft_plane_normal(hit));
	if (hit.obj->type == CYLINDER)
		return (ft_cylinder_normal(hit));
	return (vec_new(0.0, 0.0, 0.0));
}
