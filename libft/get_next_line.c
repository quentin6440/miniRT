/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcyril-a <qcyril-a@student.42lisboa.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:41:51 by qcyril-a          #+#    #+#             */
/*   Updated: 2025/03/06 19:45:02 by qcyril-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	line_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static void	buff_shift(char *buff, size_t size)
{
	int	i;

	i = 0;
	while (buff[size])
		buff[i++] = buff[size++];
	while (i < BUFFER_SIZE)
		buff[i++] = 0;
}

static char	*str_append(char *stash, char *buff)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = malloc(line_len(stash) + line_len(buff) + 2);
	if (!line)
		return (NULL);
	while (stash && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	while (buff[j] && buff[j - 1] != '\n')
		line[i++] = buff[j++];
	line[i] = 0;
	buff_shift(buff, j);
	free(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE + 1];
	char			*line;
	int				len_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	if (buff[0])
		len_read = 1;
	else
		len_read = read(fd, buff, BUFFER_SIZE);
	while (len_read > 0)
	{
		line = str_append(line, buff);
		if (!line)
			return (NULL);
		if (line[line_len(line)] == '\n')
			return (line);
		len_read = read(fd, buff, BUFFER_SIZE);
	}
	if (len_read < 0)
		return (free(line), NULL);
	return (line);
}
