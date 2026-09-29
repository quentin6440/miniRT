/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:16:05 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:16:08 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h" 	

int	ft_parse_fail(t_parse_error *error, const char *message)
{
	if (error && !error->message)
		error->message = message;
	return (-1);
}

void	ft_print_parse_error(const t_parse_error *error)
{
	if (!error || !error->message)
	{
		ft_putstr_fd("Error\nInvalid scene\n", 2);
		return ;
	}
	ft_putstr_fd("Error\n", 2);
	if (error->line > 0)
	{
		ft_putstr_fd("Line ", 2);
		ft_putnbr_fd(error->line, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((char *)error->message, 2);
}

void	ft_destroy_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->mlx_ptr)
	{
		if (scene->img_ptr && scene->img_ptr->p)
		{
			mlx_destroy_image(scene->mlx_ptr, scene->img_ptr->p);
			scene->img_ptr->p = NULL;
		}
		if (scene->win_ptr)
			mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
		scene->win_ptr = NULL;
		mlx_destroy_display(scene->mlx_ptr);
		free(scene->mlx_ptr);
		scene->mlx_ptr = NULL;
	}
	if (scene->img_ptr)
	{
		free(scene->img_ptr);
		scene->img_ptr = NULL;
	}
	ft_free_objects(&scene->objects);
	free(scene);
}
