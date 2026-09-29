/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:12:07 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:56:14 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_vec3	ft_ambient_light(t_scene *scene, t_vec3 object_color)
{
	t_vec3	ambient;

	ambient = ft_color_mul(object_color, scene->ambient.color);
	return (ft_color_scale(ambient, scene->ambient.ratio));
}

static t_vec3	ft_diffuse_light(t_scene *scene, t_hit hit)
{
	t_vec3	normal;
	t_vec3	light_dir;
	t_vec3	diffuse;
	double	intensity;

	normal = ft_get_normal(hit);
	light_dir = vec_normalize(vec_sub(scene->light.pos, hit.point));
	intensity = vec_dot(normal, light_dir);
	if (intensity < 0.0)
		intensity = 0.0;
	diffuse = ft_color_mul(hit.obj->color, scene->light.color);
	return (ft_color_scale(diffuse,
			scene->light.ratio * intensity));
}

int	ft_compute_light(t_scene *scene, t_hit hit)
{
	t_vec3	color;
	double	r;
	double	g;
	double	b;

	if (!hit.valid || !hit.obj)
		return (0);
	color = ft_ambient_light(scene, hit.obj->color);
	if (!ft_is_shadowed(scene, hit.point))
		color = ft_color_add(color, ft_diffuse_light(scene, hit));
	r = ft_color_clamp(color.x, 0.0, 255.0);
	g = ft_color_clamp(color.y, 0.0, 255.0);
	b = ft_color_clamp(color.z, 0.0, 255.0);
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}
