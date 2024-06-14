/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:18:04 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/14 20:41:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*mem;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	mem = (unsigned char *)b;
	while (i < len)
	{
		mem[i] = d;
		i++;
	}
	return (b);
}

static char	*ft_shift_left(char buffer[BUFFER_SIZE + 1], int offset)
{
	int	i;

	i = 0;
	while (buffer[i + offset])
	{
		buffer[i] = buffer[i + offset];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

static char	*splitbuf(char buffer[BUFFER_SIZE + 1], char *line, int nl_index)
{
	char	*temp;

	temp = ft_substr(buffer, 0, (nl_index + 1));
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	line = ft_strjoin(line, temp);
	free(temp);
	if (line == NULL)
	{
		ft_memset(buffer, 0, (size_t)BUFFER_SIZE + 1);
		return (NULL);
	}
	buffer = ft_shift_left(buffer, (nl_index + 1));
	return (line);
}

static char	*read_to_buf(int fd, char buffer[BUFFER_SIZE + 1])
{
	int		bts_read;
	char	*line;
	int		nl_index;

	bts_read = 1;
	line = NULL;
	nl_index = ft_strcpos(buffer, '\n');
	while (bts_read > 0 && nl_index == -1)
	{
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
		ft_memset(buffer, 0, (size_t)BUFFER_SIZE + 1);
		bts_read = read(fd, buffer, BUFFER_SIZE);
		if (bts_read == -1)
			return (free(line), NULL);
		if (bts_read == 0)
			ft_memset(buffer, 0, (size_t)BUFFER_SIZE + 1);
		nl_index = ft_strcpos(buffer, '\n');
	}
	if (bts_read > 0 && nl_index > -1)
		return (splitbuf(buffer, line, nl_index));
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[FD_SIZE][BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		ft_memset(buffer[fd], 0, (size_t)BUFFER_SIZE + 1);
		dprintf(2, "gnl 1\n");
		return (NULL);
	}
	line = read_to_buf(fd, buffer[fd]);
	if (line == NULL)
	{
		ft_memset(buffer[fd], 0, (size_t)BUFFER_SIZE + 1);
		dprintf(2, "gnl 2\n");
		return (NULL);
	}
	if (*line == '\0')
	{
		ft_memset(buffer[fd], 0, (size_t)BUFFER_SIZE + 1);
		dprintf(2, "gnl ok\n");
		free(line);
		return (NULL);
	}
	return (line);
}
