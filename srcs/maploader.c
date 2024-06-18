/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/18 18:05:08 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_mapheight(char *mapname)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(mapname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file for count\n");
		return (-1);
	}
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		//dprintf(2, "%s", line);
		free(line);
		count++;
	}
	close (fd);
	return (count);
}

// currently accepts 0-5 and space but spaces seqfault
int	validate_mapsquare(int value)
{
	if ((value >= 48 && value <= 53) || value == 32)
		return (0);
	else
		return (1);
}

static int	write_mapline(char *line, int lno, int **world_map, t_data *data)
{
	int	i;
	int	value;

	world_map[lno] = (int *)malloc(MAPWIDTH * sizeof(int));
	if (world_map[lno] == NULL)
		exit (ft_error("Map line malloc fail.\n", 1));
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		value = line[i];
		//dprintf(2, "%d", (value - 48));
		if (validate_mapsquare(value))
			exit (ft_error("Map not valid.\n", 1)); // need clean exit
		world_map[lno][i] = value - 48;
		if (value == 5) // the player start pos char, should check that exists
			data->startpos[0] = lno;
			data->startpos[1] = i;
		i++;
	}
	//dprintf(2, "\n");
	return (0);
}

// we need to have map_height and map_width in data not as defines
int	**load_map(char *mapname, t_data *data)
{
	int		fd;
	int		**world_map;
	char	*line;
	int		lno;

	data->map_height = count_mapheight(mapname);
	data->map_width = MAPWIDTH;
	//dprintf(2, "mh: %d\n", data->map_height);
	if (data->map_height <= 0 || data->map_height > MAX_MAPHEIGHT)
	{
		perror("Error opening map file (height)");
		return (NULL);
	}
	world_map = (int **)malloc((data->map_height + 1) * sizeof(int *));
	fd = open(mapname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening map file");
		return (NULL);
	}
	world_map[data->map_height] = NULL;
	lno = 0;
	while (lno <= MAX_MAPHEIGHT)
	{
		line = get_next_line(fd);
		if (!line || write_mapline(line, lno, world_map, data))
			break ;
		lno++;
	}
	close(fd);
	return (world_map);
}
