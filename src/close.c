/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by quentin           #+#    #+#             */
/*   Updated: 2026/09/28 17:51:36 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_free_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_objects(t_obj **list)
{
	t_obj	*current;
	t_obj	*next;

	if (!list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
}

void	ft_runtime_error(t_scene *scene, const char *message)
{
	ft_putstr_fd("Error\n", 2);
	if (message)
	{
		ft_putstr_fd((char *)message, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_destroy_scene(scene);
	exit(EXIT_FAILURE);
}

int	ft_clean_exit(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	ft_destroy_scene(scene);
	exit(EXIT_SUCCESS);
	return (0);
}
