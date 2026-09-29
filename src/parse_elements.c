/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by quentin           #+#    #+#             */
/*   Updated: 2026/09/29 11:14:11 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_parse_ambient(char **tokens, t_scene *scene,
		t_parse_error *error)
{
	if (!tokens || !scene)
		return (ft_parse_fail(error, "invalid ambient data"));
	if (!tokens[1] || !tokens[2] || tokens[3])
		return (ft_parse_fail(error, "invalid ambient format"));
	if (ft_str_to_float(tokens[1], &scene->ambient.ratio) != 0)
		return (ft_parse_fail(error, "invalid ambient ratio"));
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (ft_parse_fail(error, "ambient ratio out of bounds"));
	if (ft_str_to_color(tokens[2], &scene->ambient.color) != 0)
		return (ft_parse_fail(error, "invalid ambient color"));
	return (0);
}

int	ft_parse_camera(char **tokens, t_scene *scene,
		t_parse_error *error)
{
	int	result;
	
	if (!tokens || !scene)
		return (ft_parse_fail(error, "invalid camera data"));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (ft_parse_fail(error, "invalid camera format"));
	if (ft_str_to_vec3(tokens[1], &scene->camera.pos, 0) != 0)
		return (ft_parse_fail(error, "invalid camera position"));
	//if (ft_str_to_vec3(tokens[2], &scene->camera.dir, 1) != 0)
	result = ft_str_to_vec3(tokens[2], &scene->camera.dir, 1);
	if (result == VEC_NOT_NORMALIZED)
		return (ft_parse_fail(error, "camera direction is not normalized"));
	if (result != 0)
		return (ft_parse_fail(error, "invalid camera direction"));
	scene->camera.dir = vec_normalize(scene->camera.dir);
	if (ft_str_to_float(tokens[3], &scene->camera.fov) != 0)
		return (ft_parse_fail(error, "invalid camera FOV"));
	if (scene->camera.fov < 0.0 || scene->camera.fov > 180.0)
		return (ft_parse_fail(error, "camera FOV out of bounds"));
	return (0);
}

int	ft_parse_light(char **tokens, t_scene *scene,
		t_parse_error *error)
{
	if (!tokens || !scene)
		return (ft_parse_fail(error, "invalid light data"));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (ft_parse_fail(error, "invalid light format"));
	if (ft_str_to_vec3(tokens[1], &scene->light.pos, 0) != 0)
		return (ft_parse_fail(error, "invalid light position"));
	if (ft_str_to_float(tokens[2], &scene->light.ratio) != 0)
		return (ft_parse_fail(error, "invalid light ratio"));
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		return (ft_parse_fail(error, "light ratio out of bounds"));
	if (ft_str_to_color(tokens[3], &scene->light.color) != 0)
		return (ft_parse_fail(error, "invalid light color"));
	return (0);
}
