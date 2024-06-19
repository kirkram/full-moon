/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/18 18:05:08 by klukiano         ###   ########.fr       */
=======
/*   Updated: 2024/06/18 21:03:35 by mburakow         ###   ########.fr       */
>>>>>>> main
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
	while ((line = get_next_line(fd)) != NULL)
	{
<<<<<<< HEAD
		//dprintf(2, "%s", line);
=======
		if (colsmax < (int)(ft_strlen(line) - 1))
			colsmax = (int)(ft_strlen(line) - 1);
>>>>>>> main
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

static void	get_player_startpos(int x, int y, t_data *data)
{
	if (data->startpos_x || data->startpos_y)
		exit(ft_error("Duplicate starting point", 23));
	data->startpos_y = y;
	data->startpos_x = x;
}

static int	write_mapline(char *line, int lno, int **world_map, t_data *data)
{
	int	i;
	int	value;

	world_map[lno] = (int *)malloc(data->map_width * sizeof(int));
	if (world_map[lno] == NULL)
		exit (ft_error("Map line malloc fail.\n", 1));
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		value = line[i];
<<<<<<< HEAD
		//dprintf(2, "%d", (value - 48));
=======
		// dprintf(2, "%c", line[i]);
>>>>>>> main
		if (validate_mapsquare(value))
			exit (ft_error("Map not valid.\n", 1)); // need clean exit
		if (value == 78 || value == 69 || value == 83 || value == 87) // the player start pos char, should check that exists
			get_player_startpos(i, lno, data);
		world_map[lno][i] = value - 48;
		i++;
	}
<<<<<<< HEAD
	//dprintf(2, "\n");
=======
	// dprintf(2, "\n");
>>>>>>> main
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

<<<<<<< HEAD
	data->map_height = count_mapheight(mapname);
	data->map_width = MAPWIDTH;
	//dprintf(2, "mh: %d\n", data->map_height);
	if (data->map_height <= 0 || data->map_height > MAX_MAPHEIGHT)
	{
		perror("Error opening map file (height)");
		return (NULL);
	}
=======
	count_mapdimensions(mapname, data);
	if (data->map_height <= 0 || data->map_height > MAX_MAPHEIGHT
		|| data->map_width <= 0 || data->map_width > MAX_MAPWIDTH)
		exit(ft_error("Map dimensions error", 22));
>>>>>>> main
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
	return (world_map);
}
