/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:13:35 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:52:06 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_run_time(t_scene *scene)
{
	if (!scene)
		exit(EXIT_FAILURE);
	scene->win_width = 800;
	scene->win_height = 600;
	scene->mlx_ptr = mlx_init();
	if (!scene->mlx_ptr)
		ft_runtime_error(scene, "Failed to initialize MiniLibX");
	scene->win_ptr = mlx_new_window(scene->mlx_ptr,
			scene->win_width, scene->win_height,
			"miniRT - Raytracer");
	if (!scene->win_ptr)
		ft_runtime_error(scene, "Failed to create MiniLibX window");
	if (ft_put_img_to_window(scene) != 0)
		ft_runtime_error(scene, "Failed to create MiniLibX image");
	ft_render_scene(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
		scene->img_ptr->p, 0, 0);
	mlx_key_hook(scene->win_ptr, key_handler, scene);
	mlx_expose_hook(scene->win_ptr, ft_expose_handler, scene);
	mlx_hook(scene->win_ptr, 17, 0, ft_clean_exit, scene);
	mlx_loop(scene->mlx_ptr);
}
