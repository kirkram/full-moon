/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/02 19:09:03 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Rows that contain data such as texture names cannot start with space, 0 or 1
static void	count_mapdimensions(t_data *data)
{
	int		fd;
	int		rows;
	int		colsmax;
	char	*line;
	int		map_start;

	map_start = 0;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error opening map file for count\n", 22));
	rows = 0;
	colsmax = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		convert_tabs(&line);
		if (!map_start && (line[0] == 32 || line[0] == 48 || line[0] == 49))
			map_start = 1;
		if (map_start)
		{
			if (colsmax < (int)(ft_strlen(line) - 1))
				colsmax = (int)(ft_strlen(line) - 1);
			rows++;
		}
		free(line);
	}
	data->map_height = rows;
	data->map_width = colsmax;
	close(fd);
}

static void	get_player_startpos(int x, int y, t_data *data, int value)
{
	data->startpos_y = y;
	data->startpos_x = x;
	if (value == 78 || value == 69 || value == 83 || value == 87)
		if (value == 78)
			data->player->angle = rad(NORTH);
	if (value == 69)
		data->player->angle = rad(EAST);
	if (value == 83)
		data->player->angle = rad(SOUTH);
	if (value == 87)
		data->player->angle = rad(WEST);
}

static void	write_mapline(char *line, int lno, t_data *data)
{
	int	i;
	int	value;

	data->world_map[lno] = (int *)malloc(data->map_width * sizeof(int));
	if (data->world_map[lno] == NULL)
		map_validation_error("Error: map line malloc fail.\n", lno, line, data);
	i = 0;
	while (i < data->map_width)
	{
		if (line[i] != '\0' && line[i] != '\n')
		{
			value = line[i];
			if (validate_mapsquare(value))
				map_validation_error("Error: Map not valid.\n", lno + 1, line,
					data);
			if (value == 78 || value == 69 || value == 83 || value == 87)
			{
				if (data->startpos_x || data->startpos_y)
					map_validation_error("Error: duplicate starting point", lno
						+ 1, line, data);
				get_player_startpos(i, lno, data, value);
				data->world_map[lno][i] = 0;
			}
			else if (value == 32)
				data->world_map[lno][i] = 1;
			else
				data->world_map[lno][i] = value - 48;
		}
		else
		{
			while (i < data->map_width)
			{
				data->world_map[lno][i] = 1;
				i++;
			}
			break ;
		}
		i++;
	}
}

static void	read_map_parameter(char *line, t_data *data)
{
	char	*value_start;

	if (line[0] == '\n')
		return ;
	if (line[0] != 'T' || !(line[1] == 'N' || line[1] == 'E' || line[1] == 'S'
			|| line[1] == 'W') || line[2] != '=')
	{
		if (line[0] != 'C' || !(line[1] == 'C' || line[1] == 'F')
			|| line[2] != '=')
			map_validation_error("Error: invalid map parameter", 0, line, data);
	}
	value_start = ft_strchr(line, 61) + 1;
	if (value_start && (ft_strcpos(value_start, '\n') != -1))
		value_start[ft_strcpos(value_start, '\n')] = '\0';
	else
		map_validation_error("Error: invalid map parameter", 0, line, data);
	if (line[1] == 'N')
		data->nsew_path[0] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'S')
		data->nsew_path[1] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'E')
		data->nsew_path[2] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'W')
		data->nsew_path[3] = ft_strjoin("./textures/", value_start);
	else if (line[1] == 'C' || line[1] == 'F')
	{
		if (is_valid_hex(value_start))
		{
			if (line[1] == 'C')
				data->ceilingcolor = ft_atoh(value_start);
			else if (line[1] == 'F')
				data->floorcolor = ft_atoh(value_start);
		}
		else
			map_validation_error("Error: invalid map parameter", 0, line, data);
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
			write_mapline(line, lno, data);
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
