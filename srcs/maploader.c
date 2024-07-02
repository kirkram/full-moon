/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/02 19:56:59 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_with_ones(t_data *data, int y, int x)
{
	while (x < data->map_width)
	{
		data->world_map[y][x] = 1;
		x++;
	}
}

static void	allocate_mapline(char *line, int y, t_data *data)
{
	data->world_map[y] = (int *)malloc(data->map_width * sizeof(int));
	if (data->world_map[y] == NULL)
		map_validation_error("Error: map line malloc fail.\n", y, line, data);
}

static void	write_mapline(char *line, int y, int x, t_data *data)
{
	allocate_mapline(line, y, data);
	while (x < data->map_width)
	{
		if (line[x] != '\0' && line[x] != '\n')
		{
			if (validate_mapsquare(line[x]))
				map_validation_error("Error: Map not valid.\n", y + 1, line,
					data);
			if (!get_player_startpos(x, y, data, line))
			{
				if (line[x] == 32)
					data->world_map[y][x] = 1;
				else
					data->world_map[y][x] = line[x] - 48;
			}
		}
		else
		{
			fill_with_ones(data, y, x);
			break ;
		}
		x++;
	}
}

void	load_map(t_data *data)
{
	int		fd;
	char	*line;
	int		lno;
	int		map_start;

	map_start = 0;
	count_mapdimensions(data);
	if (data->map_height <= 0 || data->map_height > MAX_MAPHEIGHT
		|| data->map_width <= 0 || data->map_width > MAX_MAPWIDTH)
		map_validation_error("Error: invalid map dimensions", data->map_height,
			NULL, data);
	data->world_map = (int **)malloc((data->map_height + 1) * sizeof(int *));
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error opening map file", 12));
	data->world_map[data->map_height] = NULL;
	lno = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		convert_tabs(&line);
		if (map_start == 0 && (line[0] == 32 || line[0] == 48 || line[0] == 49))
			map_start = 1;
		if (map_start == 1)
		{
			write_mapline(line, lno, 0, data);
			lno++;
		}
		if (map_start == 0)
			read_map_parameter(line, data);
		free(line);
	}
	close(fd);
	if (data->startpos_x == 0 || data->startpos_y == 0)
		map_validation_error("Error: no player starting point",
			data->map_height, NULL, data);
	if (data->ceilingcolor == 0x0)
		data->ceilingcolor = CEILING;
	if (data->floorcolor == 0x0)
		data->floorcolor = FLOOR;
	return ;
}
