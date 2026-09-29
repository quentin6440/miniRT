/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cl_cap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:13:44 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:13:45 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static double	ft_check_cap_plane(t_ray ray, t_vec3 center,
		t_vec3 normal, double radius)
{
	double	denom;
	double	t;
	t_vec3	point;
	t_vec3	distance;

	denom = vec_dot(ray.dir, normal);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = vec_dot(vec_sub(center, ray.origin), normal) / denom;
	if (t <= EPSILON)
		return (-1.0);
	point = vec_add(ray.origin, vec_scale(ray.dir, t));
	distance = vec_sub(point, center);
	if (vec_dot(distance, distance) <= radius * radius)
		return (t);
	return (-1.0);
}

static double	ft_check_cap(t_obj *obj, t_ray ray,
		t_vec3 axis, int top)
{
	t_vec3	center;
	t_vec3	normal;
	double	radius;

	radius = obj->diameter / 2.0;
	if (top)
	{
		center = vec_add(obj->pos,
				vec_scale(axis, obj->height / 2.0));
		normal = axis;
	}
	else
	{
		center = vec_sub(obj->pos,
				vec_scale(axis, obj->height / 2.0));
		normal = vec_scale(axis, -1.0);
	}
	return (ft_check_cap_plane(ray, center, normal, radius));
}

double	ft_hit_cylinder_caps(t_obj *obj, t_ray ray, t_vec3 *out_norm)
{
	t_vec3	axis;
	double	t_bottom;
	double	t_top;

	axis = vec_normalize(obj->dir);
	t_bottom = ft_check_cap(obj, ray, axis, 0);
	t_top = ft_check_cap(obj, ray, axis, 1);
	if (t_bottom > EPSILON
		&& (t_top <= EPSILON || t_bottom < t_top))
	{
		if (out_norm)
			*out_norm = vec_scale(axis, -1.0);
		return (t_bottom);
	}
	if (t_top > EPSILON)
	{
		if (out_norm)
			*out_norm = axis;
		return (t_top);
	}
	return (-1.0);
}
