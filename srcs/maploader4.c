/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:41:09 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/31 15:46:37 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_end(char *line, int fd)
{
	if (line[0] == '\n')
	{
		if (ft_strlen(line) > 1)
		{
			close(fd);
			free(line);
			exit(ft_error("Error\nInvalid map data (end)\n", 24));
		}
		return (2);
	}
	return (1);
}

static int	count_mapdimensions_loop(t_data *data, char *line,
		int map_start_end, int fd)
{
	line = get_next_line(fd);
	if (!line)
		return (1);
	convert_tabs(&line);
	if (!map_start_end && (line[0] == 32 || line[0] == 48 || line[0] == 49))
		map_start_end = 1;
	if (map_start_end == 1)
	{
		map_start_end = check_map_end(line, fd);
		if (data->map_width < (int)(ft_strlen(line) - 1))
			data->map_width = (int)(ft_strlen(line) - 1);
		data->map_height++;
	}
	if (map_start_end == 2)
	{
		close(fd);
		free(line);
		exit(ft_error("Error\nInvalid map data (lines)\n", 24));
	}
	free(line);
	return (0);
}

// Rows that contain data such as texture names cannot start with space, 0 or 1
void	count_mapdimensions(t_data *data)
{
	int		fd;
	char	*line;
	int		map_start_end;

	map_start_end = 0;
	line = NULL;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error\nCant open map file for count\n", 22));
	while (1)
	{
		if (count_mapdimensions_loop(data, line, map_start_end, fd))
			break ;
	}
	close(fd);
}

int	check_map_format(t_data *data)
{
	int	len;

	len = ft_strlen(data->map_path);
	if (len < 5)
		return (0);
	if (len >= 5 && data->map_path[len - 5] == '/')
		return (0);
	return (ft_strncmp(data->map_path + len - 4, ".cub", 4) == 0);
}
