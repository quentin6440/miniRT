/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 22:00:00 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 15:41:23 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static double	ft_get_obj_t(t_obj *obj, t_ray ray)
{
	if (obj->type == SPHERE)
		return (ft_hit_sphere(obj, ray));
	if (obj->type == PLANE)
		return (ft_hit_plane(obj, ray));
	if (obj->type == CYLINDER)
		return (ft_hit_cylinder(obj, ray));
	return (-1.0);
}

t_hit	ft_intersect_scene(t_scene *scene, t_ray ray)
{
	t_hit	hit;
	t_obj	*obj;
	double	t;

	hit.valid = 0;
	hit.t = 1e30;
	hit.obj = NULL;
	hit.point = vec_new(0, 0, 0);
	obj = scene->objects;
	while (obj)
	{
		t = ft_get_obj_t(obj, ray);
		if (t > EPSILON && t < hit.t)
		{
			hit.valid = 1;
			hit.t = t;
			hit.obj = obj;
		}
		obj = obj->next;
	}
	if (hit.valid)
		hit.point = vec_add(ray.origin,
				vec_scale(ray.dir, hit.t));
	return (hit);
}
