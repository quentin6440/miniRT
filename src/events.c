/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by quentin           #+#    #+#             */
/*   Updated: 2026/09/28 18:58:52 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	key_handler(int key, void *param)
{
	if (key == ESC || key == ESC_1)
		ft_clean_exit(param);
	return (0);
}

int	ft_expose_handler(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (!scene || !scene->mlx_ptr || !scene->win_ptr
		|| !scene->img_ptr || !scene->img_ptr->p)
		return (0);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr,
		scene->img_ptr->p, 0, 0);
	return (0);
}
