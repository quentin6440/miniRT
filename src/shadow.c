/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 22:00:00 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 17:53:30 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static double	ft_shadow_t(t_obj *obj, t_ray ray)
{
	if (obj->type == SPHERE)
		return (ft_hit_sphere(obj, ray));
	if (obj->type == PLANE)
		return (ft_hit_plane(obj, ray));
	if (obj->type == CYLINDER)
		return (ft_hit_cylinder(obj, ray));
	return (-1.0);
}

int	ft_is_shadowed(t_scene *scene, t_vec3 point)
{
	t_ray	ray;
	t_vec3	to_light;
	t_obj	*obj;
	double	light_distance;
	double	t;

	to_light = vec_sub(scene->light.pos, point);
	light_distance = vec_length(to_light);
	if (light_distance < EPSILON)
		return (0);
	ray.origin = vec_add(point,
			vec_scale(vec_normalize(to_light), EPSILON * 10.0));
	ray.dir = vec_normalize(to_light);
	obj = scene->objects;
	while (obj)
	{
		t = ft_shadow_t(obj, ray);
		if (t > EPSILON && t < light_distance)
			return (1);
		obj = obj->next;
	}
	return (0);
}
