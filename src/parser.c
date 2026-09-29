/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by quentin           #+#    #+#             */
/*   Updated: 2026/09/28 17:41:58 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	ft_is_identifier(char *identifier, char *expected)
{
	return (ft_strncmp(identifier, expected,
			ft_strlen(expected) + 1) == 0);
}

static int	ft_parse_unique(char **tokens, t_scene *scene,
		t_parse_error *error, t_global_parser config)
{
	if (*config.seen)
		return (ft_parse_fail(error, config.duplicate_message));
	if (config.parser(tokens, scene, error) < 0)
		return (-1);
	*config.seen = 1;
	return (0);
}

static int	ft_parse_global(char **tokens, t_scene *scene,
		t_parse_error *error)
{
	if (ft_is_identifier(tokens[0], "A"))
		return (ft_parse_unique(tokens, scene, error,
				(t_global_parser){&scene->has_ambient,
				ft_parse_ambient, "duplicate ambient element"}));
	if (ft_is_identifier(tokens[0], "C"))
		return (ft_parse_unique(tokens, scene, error,
				(t_global_parser){&scene->has_camera,
				ft_parse_camera, "duplicate camera element"}));
	if (ft_is_identifier(tokens[0], "L"))
		return (ft_parse_unique(tokens, scene, error,
				(t_global_parser){&scene->has_light,
				ft_parse_light, "duplicate light element"}));
	return (1);
}

int	ft_parse_line(char **tokens, t_scene *scene,
		t_parse_error *error)
{
	int	result;

	if (!tokens || !tokens[0] || !scene)
		return (ft_parse_fail(error, "invalid scene line"));
	result = ft_parse_global(tokens, scene, error);
	if (result != 1)
		return (result);
	if (ft_is_identifier(tokens[0], "sp"))
		return (ft_parse_obj(tokens, scene, SPHERE, error));
	if (ft_is_identifier(tokens[0], "pl"))
		return (ft_parse_obj(tokens, scene, PLANE, error));
	if (ft_is_identifier(tokens[0], "cy"))
		return (ft_parse_obj(tokens, scene, CYLINDER, error));
	return (ft_parse_fail(error, "unknown scene element"));
}
