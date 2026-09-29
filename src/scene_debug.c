/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:13:12 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/28 18:13:13 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <stdio.h>

static void	ft_print_objects(t_scene *scene)
{
	t_obj	*obj;
	int		i;

	printf("--- Objets dans la liste ---\n");
	obj = scene->objects;
	i = 1;
	while (obj)
	{
		if (obj->type == SPHERE)
			printf("[%d] SPHERE: pos=[%.1f,%.1f,%.1f], diam=%.1f\n",
				i, obj->pos.x, obj->pos.y, obj->pos.z,
				obj->diameter);
		else if (obj->type == PLANE)
			printf("[%d] PLANE: pos=[%.1f,%.1f,%.1f]\n",
				i, obj->pos.x, obj->pos.y, obj->pos.z);
		else if (obj->type == CYLINDER)
			printf("[%d] CYLINDER: pos=[%.1f,%.1f,%.1f], diam=%.1f, h=%.1f\n",
				i, obj->pos.x, obj->pos.y, obj->pos.z,
				obj->diameter, obj->height);
		obj = obj->next;
		i++;
	}
}

void	ft_print_scene_info(t_scene *scene)
{
	printf("=== CONTENU DE LA SCENE ===\n");
	printf("Ambient: ratio=%.2f, color=[%.0f,%.0f,%.0f]\n",
		scene->ambient.ratio, scene->ambient.color.x,
		scene->ambient.color.y, scene->ambient.color.z);
	printf("Camera: pos=[%.1f,%.1f,%.1f], dir=[%.1f,%.1f,%.1f]\n",
		scene->camera.pos.x, scene->camera.pos.y,
		scene->camera.pos.z, scene->camera.dir.x,
		scene->camera.dir.y, scene->camera.dir.z);
	printf("Camera FOV: %.0f\n", scene->camera.fov);
	printf("Light: pos=[%.1f,%.1f,%.1f], ratio=%.2f\n",
		scene->light.pos.x, scene->light.pos.y,
		scene->light.pos.z, scene->light.ratio);
	ft_print_objects(scene);
}
