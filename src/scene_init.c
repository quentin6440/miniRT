/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:13:19 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:13:20 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <fcntl.h>

static int	ft_open_scene(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open .rt file\n", 2);
		return (-1);
	}
	return (fd);
}

static int	ft_init_scene(t_scene **scene)
{
	*scene = ft_calloc(1, sizeof(t_scene));
	if (!*scene)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (-1);
	}
	(*scene)->img_ptr = ft_calloc(1, sizeof(t_img));
	if (!(*scene)->img_ptr)
	{
		ft_destroy_scene(*scene);
		*scene = NULL;
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_load_scene(char *path, t_scene **scene)
{
	t_parse_error	error;
	int				fd;

	fd = ft_open_scene(path);
	if (fd < 0)
		return (-1);
	if (ft_init_scene(scene) < 0)
	{
		close(fd);
		return (-1);
	}
	if (ft_parse_rt(fd, *scene, &error) < 0)
	{
		close(fd);
		ft_print_parse_error(&error);
		ft_destroy_scene(*scene);
		*scene = NULL;
		return (-1);
	}
	close(fd);
	return (0);
}
