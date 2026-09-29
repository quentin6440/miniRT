/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:15:02 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:15:22 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	ft_check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 3) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	scene = NULL;
	if (ft_check_args(argc, argv))
	{
		ft_putstr_fd("Error\nUsage: ./miniRT <scene.rt>\n", 2);
		return (EXIT_FAILURE);
	}
	if (ft_load_scene(argv[1], &scene) < 0)
		return (EXIT_FAILURE);
	ft_print_scene_info(scene);
	ft_run_time(scene);
	ft_destroy_scene(scene);
	return (EXIT_SUCCESS);
}
