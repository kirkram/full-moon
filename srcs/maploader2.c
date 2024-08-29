/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:05:11 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 14:36:59 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_with_nines(t_data *data, int y, int x)
{
	while (x < data->map_width)
	{
		data->world_map[y][x] = 9;
		x++;
	}
}

int		check_map_end(char *line, int fd)
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
	return(1);
}

// Rows that contain data such as texture names cannot start with space, 0 or 1
void	count_mapdimensions(t_data *data)
{
	int		fd;
	char	*line;
	int		map_start_end;

	map_start_end = 0;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error\nCant open map file for count\n", 22));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
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
	}
	close(fd);
}

int	get_player_startpos(int x, int y, t_data *data, char *line)
{
	if (line[x] == 78 || line[x] == 69 || line[x] == 83 || line[x] == 87)
	{
		if (data->startpos_x || data->startpos_y)
			map_validation_error("Error\nDuplicate starting point", y + 1, line,
				data);
		data->startpos_y = y;
		data->startpos_x = x;
		if (line[x] == 78)
			data->player->angle = rad(NORTH);
		if (line[x] == 69)
			data->player->angle = rad(EAST);
		if (line[x] == 83)
			data->player->angle = rad(SOUTH);
		if (line[x] == 87)
			data->player->angle = rad(WEST);
		data->world_map[y][x] = 0;
		return (1);
	}
	return (0);
}

static void	replace_tabs_with_spaces(const char *input_line, char *output_line)
{
	int	i;
	int	j;
	int	input_len;
	int	output_index;
	int	space_count;

	input_len = ft_strlen(input_line);
	output_index = 0;
	i = -1;
	while (++i < input_len)
	{
		if (input_line[i] == '\t')
		{
			space_count = TAB_WIDTH - (output_index % TAB_WIDTH);
			j = -1;
			while (++j < space_count)
				output_line[output_index++] = ' ';
		}
		else
			output_line[output_index++] = input_line[i];
	}
	output_line[output_index] = '\0';
}

void	convert_tabs(char **line)
{
	char	output_line[MAX_MAPWIDTH * TAB_WIDTH];

	replace_tabs_with_spaces(*line, output_line);
	free(*line);
	*line = ft_strdup(output_line);
}
