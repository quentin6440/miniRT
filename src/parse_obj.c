/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:11:34 by qcyril-a          #+#    #+#             */
/*   Updated: 2026/09/29 11:20:21 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	ft_obj_add_back(t_obj **list, t_obj *new_obj)
{
	t_obj	*current;

	if (!list || !new_obj)
		return ;
	if (!*list)
	{
		*list = new_obj;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_obj;
}

static int	ft_fill_sphere(t_obj *obj, char **tokens,
		t_parse_error *error)
{
	if (!tokens || !tokens[1] || !tokens[2]
		|| !tokens[3] || tokens[4])
		return (ft_parse_fail(error, "invalid sphere format"));
	if (ft_str_to_vec3(tokens[1], &obj->pos, 0) != 0)
		return (ft_parse_fail(error, "invalid sphere position"));
	if (ft_str_to_float(tokens[2], &obj->diameter) != 0)
		return (ft_parse_fail(error, "invalid sphere diameter"));
	if (obj->diameter <= 0.0)
		return (ft_parse_fail(error,
				"sphere diameter must be positive"));
	if (ft_str_to_color(tokens[3], &obj->color) != 0)
		return (ft_parse_fail(error, "invalid sphere color"));
	return (0);
}

static int	ft_fill_plane(t_obj *obj, char **tokens,
		t_parse_error *error)
{
	int	result;

	if (!tokens || !tokens[1] || !tokens[2]
		|| !tokens[3] || tokens[4])
		return (ft_parse_fail(error, "invalid plane format"));
	if (ft_str_to_vec3(tokens[1], &obj->pos, 0) != 0)
		return (ft_parse_fail(error, "invalid plane position"));
	//if (ft_str_to_vec3(tokens[2], &obj->dir, 1) != 0)
	result = ft_str_to_vec3(tokens[2], &obj->dir, 1);
	if (result == VEC_NOT_NORMALIZED)
		return (ft_parse_fail(error, "plane direction is not normalized"));
	if (result != 0)
		return (ft_parse_fail(error, "invalid plane direction"));
	obj->dir = vec_normalize(obj->dir);
	if (ft_str_to_color(tokens[3], &obj->color) != 0)
		return (ft_parse_fail(error, "invalid plane color"));
	return (0);
}

static int	ft_fill_cylinder(t_obj *obj, char **tokens,
		t_parse_error *error)
{
	int result;
	
	if (!tokens || !tokens[1] || !tokens[2]
		|| !tokens[3] || !tokens[4]
		|| !tokens[5] || tokens[6])
		return (ft_parse_fail(error, "invalid cylinder format"));
	if (ft_str_to_vec3(tokens[1], &obj->pos, 0) != 0)
		return (ft_parse_fail(error, "invalid cylinder position"));
	//if (ft_str_to_vec3(tokens[2], &obj->dir, 1) != 0)
	result = ft_str_to_vec3(tokens[2], &obj->dir, 1);
	if (result == VEC_NOT_NORMALIZED)
		return (ft_parse_fail(error, "plane direction is not normalized"));
	if (result != 0)
		return (ft_parse_fail(error, "invalid cylinder direction"));
	obj->dir = vec_normalize(obj->dir);
	if (ft_str_to_float(tokens[3], &obj->diameter) != 0)
		return (ft_parse_fail(error, "invalid cylinder diameter"));
	if (obj->diameter <= 0.0)
		return (ft_parse_fail(error,
				"cylinder diameter must be positive"));
	if (ft_str_to_float(tokens[4], &obj->height) != 0)
		return (ft_parse_fail(error, "invalid cylinder height"));
	if (obj->height <= 0.0)
		return (ft_parse_fail(error,
				"cylinder height must be positive"));
	if (ft_str_to_color(tokens[5], &obj->color) != 0)
		return (ft_parse_fail(error, "invalid cylinder color"));
	return (0);
}

int	ft_parse_obj(char **tokens, t_scene *scene, t_type type,
		t_parse_error *error)
{
	t_obj	*new_obj;

	if (!tokens || !scene)
		return (ft_parse_fail(error, "invalid object data"));
	new_obj = ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		return (ft_parse_fail(error, "memory allocation failed"));
	new_obj->type = type;
	if (type == SPHERE
		&& ft_fill_sphere(new_obj, tokens, error) < 0)
		return (free(new_obj), -1);
	if (type == PLANE
		&& ft_fill_plane(new_obj, tokens, error) < 0)
		return (free(new_obj), -1);
	if (type == CYLINDER
		&& ft_fill_cylinder(new_obj, tokens, error) < 0)
		return (free(new_obj), -1);
	ft_obj_add_back(&scene->objects, new_obj);
	return (0);
}
