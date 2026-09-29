/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by quentin           #+#    #+#             */
/*   Updated: 2026/09/28 17:49:59 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	ft_normalize_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
}

static void	ft_init_parse_error(t_parse_error *error)
{
	error->line = 0;
	error->message = NULL;
}

static int	ft_check_required(t_scene *scene, t_parse_error *error)
{
	if (!scene->has_ambient
		|| !scene->has_camera
		|| !scene->has_light)
		return (ft_parse_fail(error,
				"missing mandatory scene element"));
	return (0);
}

static int	ft_parse_raw_line(char *raw_line, t_scene *scene,
		t_parse_error *error)
{
	char	*clean_line;
	char	**tokens;
	int		result;

	clean_line = ft_strtrim(raw_line, " \t\r\n\v\f");
	free(raw_line);
	if (!clean_line)
		return (ft_parse_fail(error, "memory allocation failed"));
	if (clean_line[0] == '\0' || clean_line[0] == '#')
	{
		free(clean_line);
		return (0);
	}
	ft_normalize_spaces(clean_line);
	tokens = ft_split(clean_line, ' ');
	if (!tokens)
	{
		free(clean_line);
		return (ft_parse_fail(error, "memory allocation failed"));
	}
	result = ft_parse_line(tokens, scene, error);
	ft_free_tab(tokens);
	free(clean_line);
	return (result);
}

int	ft_parse_rt(int fd, t_scene *scene, t_parse_error *error)
{
	char	*raw_line;
	int		line_number;
	int		result;

	if (fd < 0 || !scene || !error)
		return (-1);
	ft_init_parse_error(error);
	line_number = 0;
	raw_line = get_next_line(fd);
	while (raw_line)
	{
		line_number++;
		result = ft_parse_raw_line(raw_line, scene, error);
		if (result < 0)
		{
			error->line = line_number;
			return (-1);
		}
		raw_line = get_next_line(fd);
	}
	return (ft_check_required(scene, error));
}
