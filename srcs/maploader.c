/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/16 13:26:47 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				if (line[x] == ' ')
					data->world_map[y][x] = 1;
				else if (line[x] == '5')
					add_new_enemy(x, y, data, line);
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

static void	get_floor_and_ceiling_colors(t_data *data)
{
	if (data->ceilingcolor == 0x0)
	{
		printf("No ceiling color found, default SKYBLUE\n");
		data->ceilingcolor = CEILING;
	}
	if (data->floorcolor == 0x0)
	{
		printf("No floor color found, default GRAY\n");
		data->floorcolor = FLOOR;
	}
}

static void	read_and_parse_lines(int fd, t_data *data)
{
	char	*line;
	size_t	lno;
	int		map_start;
	int		i;

	map_start = 0;
	lno = 0;
	while (1)
	{
		printf("L: $");
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		convert_tabs(&line);
		if (map_start == 0 && (line[0] == 9 || line[0] == 32 || 
				line[0] == 48 || line[0] == 49))
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
	printf("All lines have been read\n");
	// data->world_map[data->map_width][lno] = '\0';
	// For debug:
	i = -1;
	while (data->enemies && data->enemies[++i] != NULL)
	{
		printf("Enemy %d: x:%.0f y:%.0f\n", i, data->enemies[i]->x_pos, data->enemies[i]->y_pos);
	}
}

void	load_map(t_data *data)
{
	int	fd;

	count_mapdimensions(data);
	if (data->map_height <= 0 || data->map_height > MAX_MAPHEIGHT
		|| data->map_width <= 0 || data->map_width > MAX_MAPWIDTH)
		map_validation_error("Error: invalid map dimensions", data->map_height,
			NULL, data);
	data->world_map = (int **)malloc((data->map_height + 1) * sizeof(int *));
	if (!data->world_map)
		map_validation_error("Error: world map allocation", data->map_height,
			NULL, data);
	data->world_map[data->map_height] = NULL;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error opening map file", 12));
	read_and_parse_lines(fd, data);
	close(fd);
	get_floor_and_ceiling_colors(data);
	return ;
}
