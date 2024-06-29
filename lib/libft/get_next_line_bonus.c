/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:18:04 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/29 14:54:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_shift_left(char buffer[BUFFER_SIZE + 1], int offset)
{
	int	i;

	i = 0;
	while (buffer[i + offset])
	{
		buffer[i] = buffer[i + offset];
		i++;
	}
	buffer[i] = '\0';
}

static char	*splitbuf(char buffer[BUFFER_SIZE + 1], char *line, int nl_index)
{
	char	*temp;
	char	*new_line;

	temp = ft_substr(buffer, 0, nl_index + 1);
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	new_line = ft_strjoin(line, temp);
	free(temp);
	free(line);
	if (!new_line)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (NULL);
	}
	ft_shift_left(buffer, nl_index + 1);
	return (new_line);
}

static char	*read_and_append(int fd, char **line, char buffer[BUFFER_SIZE + 1])
{
	int		bts_read;
	char	*tmp;

	tmp = ft_strjoin(*line, buffer);
	free(*line);
	if (!tmp)
		return (NULL);
	*line = tmp;
	ft_bzero(buffer, BUFFER_SIZE + 1);
	bts_read = read(fd, buffer, BUFFER_SIZE);
	if (bts_read == -1)
	{
		free(*line);
		return (NULL);
	}
	return (*line);
}

static char	*read_to_buf(int fd, char buffer[BUFFER_SIZE + 1])
{
	char	*line;
	int		nl_index;

	line = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	nl_index = ft_strcpos(buffer, '\n');
	while (nl_index == -1)
	{
		if (!read_and_append(fd, &line, buffer))
			return (NULL);
		if (buffer[0] == '\0')
			break ;
		nl_index = ft_strcpos(buffer, '\n');
	}
	if (nl_index > -1)
		return (splitbuf(buffer, line, nl_index));
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[FD_SIZE][BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0)
			ft_bzero(buffer[fd], BUFFER_SIZE + 1);
		return (NULL);
	}
	line = read_to_buf(fd, buffer[fd]);
	if (line == NULL)
	{
		ft_bzero(buffer[fd], BUFFER_SIZE + 1);
		return (NULL);
	}
	if (*line == '\0')
	{
		ft_bzero(buffer[fd], BUFFER_SIZE + 1);
		free(line);
		return (NULL);
	}
	return (line);
}
