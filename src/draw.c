/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 13:32:19 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 17:51:41 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_put_pixel(int x, int y, unsigned int color, t_scene *scene)
{
	int		i;
	int		bytes_per_pixel;
	char	*pixel;

	if (!scene || !scene->img_ptr || !scene->img_ptr->data)
		return ;
	if (x < 0 || y < 0 || x >= scene->win_width || y >= scene->win_height)
		return ;
	bytes_per_pixel = scene->img_ptr->bits_per_pixel / 8;
	if (bytes_per_pixel <= 0)
		return ;
	i = y * scene->img_ptr->line_len + x * bytes_per_pixel;
	pixel = scene->img_ptr->data + i;
	*(unsigned int *)pixel = color;
}
