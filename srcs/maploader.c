/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/21 16:26:17 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// width of the map is always the length of the longest row, need to handle shorter
// rows 
static void	count_mapdimensions(char *mapname, t_data *data)
{
	int		fd;
	int		rows;
	int		colsmax;
	char	*line;

	fd = open(mapname, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error opening file for count\n", 22));
	rows = 0;
	colsmax = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (colsmax < (int)(ft_strlen(line) - 1))
			colsmax = (int)(ft_strlen(line) - 1);
		free(line);
		rows++;
	}
	data->map_height = rows;
	data->map_width = colsmax;
	close (fd);
}

// currently accepts 0-5 and space but spaces seqfault
static int	validate_mapsquare(int value)
{
	if (value == 48 || value == 49 || value == 32)
		return (0);
	else if (value == 78 || value == 69 || value == 83 || value == 87)
		return (0);
	else
		return (1);
}

static void	get_player_startpos(int x, int y, t_data *data, int value)
{
	// if (data->startpos_x || data->startpos_y)
	// 	exit(ft_error("Duplicate starting point", 23));
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

static int	write_mapline(char *line, int lno, int **world_map, t_data *data)
{
	int	i;
	int	value;

	world_map[lno] = (int *)malloc(data->map_width * sizeof(int));
	if (world_map[lno] == NULL)
		exit (ft_error("Map line malloc fail.\n", 1));
	i = 0;
	while (i < data->map_width)
	{
		if (line[i] != '\0' && line[i] != '\n')
		{
			value = line[i];
			// dprintf(2, "%c", line[i]);
			if (validate_mapsquare(value))
				exit (ft_error("Map not valid.\n", 1)); // need clean exit
			if (value == 78 || value == 69 || value == 83 || value == 87) // the player start pos char, should check that exists
			{
				get_player_startpos(i, lno, data, value);
				world_map[lno][i] = 0;
			}
			// TEMP: 3 following lines
			else if (value == 32)
				world_map[lno][i] = 1;
			else	
				world_map[lno][i] = value - 48;
		}
		else
			world_map[lno][i] = 1;
		i++;
	}
	return (0);
}

// we need to have map_height and map_width in data not as defines
// right now assumes a square map, but we need to handle spaces correctly
int	**load_map(char *mapname, t_data *data)
{
	int		fd;
	int		**world_map;
	char	*line;
	int		lno;

	count_mapdimensions(mapname, data);
	if (data->map_height <= 0 || data->map_height > MAX_MAPHEIGHT
		|| data->map_width <= 0 || data->map_width > MAX_MAPWIDTH)
		exit(ft_error("Map dimensions error", 22));
	world_map = (int **)malloc((data->map_height + 1) * sizeof(int *));
	fd = open(mapname, O_RDONLY);
	if (fd == -1)
		exit(ft_error("Error opening map file", 12));
	world_map[data->map_height] = NULL;
	lno = 0;
	while (lno <= MAX_MAPHEIGHT)
	{
		line = get_next_line(fd);
		if (!line || write_mapline(line, lno, world_map, data))
			break ;
		free(line);
		lno++;
	}
	close(fd);
	print_2d_int(world_map, data->map_height, data->map_width);
	return (world_map);
}
