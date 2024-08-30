/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 18:32:44 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	allocate_mapline(char *line, int y, t_data *data)
{
	data->world_map[y] = (int *)malloc(data->map_width * sizeof(int));
	if (data->world_map[y] == NULL)
		map_validation_error("Error\nMap line malloc fail.\n", y, line, data);
}

static void	write_mapline(char *line, int y, int x, t_data *data)
{
	allocate_mapline(line, y, data);
	while (x < data->map_width)
	{
		if (line[x] != '\0' && line[x] != '\n')
		{
			if (validate_mapsquare(line[x]))
				map_validation_error("Error\nMap not valid.\n", y + 1, line,
					data);
			if (!get_player_startpos(x, y, data, line))
			{
				if (line[x] == ' ')
					data->world_map[y][x] = 9;
				else if (line[x] == '5')
					add_new_enemy(x, y, data, line);
				else
					data->world_map[y][x] = line[x] - 48;
			}
		}
		else
		{
			fill_with_nines(data, y, x);
			break ;
		}
		x++;
	}
}

static void	get_floor_and_ceiling_colors(t_data *data)
{
	if (data->ceilingcolor == 0x0)
	{
		map_validation_error("Error\nMissing color value", data->map_height,
			NULL, data);
	}
	if (data->floorcolor == 0x0)
	{
		map_validation_error("Error\nMissing color value", data->map_height,
			NULL, data);
	}
}

static void	read_and_parse_lines(int fd, t_data *data)
{
	char	*line;
	size_t	lno;
	int		map_start;

	map_start = 0;
	lno = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		convert_tabs(&line);
		if (map_start == 0 && (line[0] == 9 || line[0] == 32
				|| line[0] == 48 || line[0] == 49))
			map_start = 1;
		if (map_start == 0)
			read_map_parameter(line, data);
		if (map_start == 1)
		{
			write_mapline(line, lno, 0, data);
			lno++;
		}
		free(line);
	}
}

int		check_map_format(t_data *data)
{
	int		len;

	len = ft_strlen(data->map_path);
	if (len < 5)
		return (0);
	if (len >= 5 && data->map_path[len - 5] == '/')
		return (0);
	return (ft_strncmp(data->map_path + len - 4, ".cub", 4) == 0);	
}

void	load_map(t_data *data)
{
	int	fd;

	if (!check_map_format(data))
		map_validation_error("Error\nInvalid map format", data->map_height,
			NULL, data);
	count_mapdimensions(data);
	if (data->map_height <= 0 || data->map_height > MAX_MAPHEIGHT
		|| data->map_width <= 0 || data->map_width > MAX_MAPWIDTH)
		map_validation_error("Error\nInvalid map dimensions", data->map_height,
			NULL, data);
	data->world_map = (int **)malloc((data->map_height + 1) * sizeof(int *));
	if (!data->world_map)
		map_validation_error("Error\nWorld map allocation", data->map_height,
			NULL, data);
	data->world_map[data->map_height] = NULL;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error\nCan't open map file", 12));
	read_and_parse_lines(fd, data);
	close(fd);
	get_floor_and_ceiling_colors(data);
	return ;
}
