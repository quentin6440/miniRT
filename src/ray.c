/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:34:04 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:11:51 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_vec3	ft_get_world_up(t_vec3 forward)
{
	if (fabs(forward.y) > 0.999)
	{
		if (forward.y > 0.0)
			return (vec_new(0.0, 0.0, -1.0));
		return (vec_new(0.0, 0.0, 1.0));
	}
	return (vec_new(0.0, 1.0, 0.0));
}

static t_basis	ft_build_basis(t_vec3 forward)
{
	t_basis	basis;
	t_vec3	world_up;

	world_up = ft_get_world_up(forward);
	basis.forward = forward;
	basis.right = vec_normalize(vec_cross(world_up, forward));
	basis.up = vec_cross(forward, basis.right);
	return (basis);
}

static t_ray_view	ft_build_view(t_camera *cam, t_scene *scene)
{
	t_ray_view	view;

	view.basis = ft_build_basis(vec_normalize(cam->dir));
	view.aspect_ratio = (double)scene->win_width
		/ (double)scene->win_height;
	view.fov_adjustment = tan((cam->fov * M_PI / 180.0) / 2.0);
	return (view);
}

static t_vec3	ft_build_ray_dir(t_ray_view view, double u, double v)
{
	t_vec3	direction;

	direction = vec_scale(view.basis.right,
			(2.0 * u - 1.0)
			* view.aspect_ratio * view.fov_adjustment);
	direction = vec_add(direction,
			vec_scale(view.basis.up,
				(1.0 - 2.0 * v) * view.fov_adjustment));
	direction = vec_add(view.basis.forward, direction);
	return (vec_normalize(direction));
}

t_ray	ft_generate_ray(t_camera *cam, double u, double v, t_scene *scene)
{
	t_ray		ray;
	t_ray_view	view;

	view = ft_build_view(cam, scene);
	ray.origin = cam->pos;
	ray.dir = ft_build_ray_dir(view, u, v);
	return (ray);
}
