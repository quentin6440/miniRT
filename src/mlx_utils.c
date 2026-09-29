/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:12:24 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:12:30 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_put_img_to_window(t_scene *scene)
{
	if (!scene || !scene->mlx_ptr || !scene->img_ptr)
		return (1);
	if (scene->img_ptr->p)
		mlx_destroy_image(scene->mlx_ptr, scene->img_ptr->p);
	scene->img_ptr->p = mlx_new_image(scene->mlx_ptr,
			scene->win_width, scene->win_height);
	if (!scene->img_ptr->p)
		return (1);
	scene->img_ptr->data = mlx_get_data_addr(scene->img_ptr->p,
			&scene->img_ptr->bits_per_pixel,
			&scene->img_ptr->line_len,
			&scene->img_ptr->endian);
	if (!scene->img_ptr->data)
	{
		mlx_destroy_image(scene->mlx_ptr, scene->img_ptr->p);
		scene->img_ptr->p = NULL;
		return (1);
	}
	return (0);
}

void	ft_mlx_pixel_put(t_scene *scene, int x, int y, int color)
{
	char	*dst;

	if (!scene || !scene->img_ptr || !scene->img_ptr->data)
		return ;
	if (x < 0 || x >= scene->win_width
		|| y < 0 || y >= scene->win_height)
		return ;
	dst = scene->img_ptr->data + (y * scene->img_ptr->line_len
			+ x * (scene->img_ptr->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
