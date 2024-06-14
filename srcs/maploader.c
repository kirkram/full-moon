/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:51:52 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/14 21:50:04 by mburakow         ###   ########.fr       */
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
	// else 
		// dprintf(2, "Opened file.\n");
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		dprintf(2, "%s", line);
		free(line);
		count++;
	}
	close (fd);
	return (count);
}

static int	write_mapline(char *line, int lno, int **world_map)
{
	int		i;
	char	value[1];

	world_map[lno] = (int *)malloc(MAPWIDTH * sizeof(int));
	if (world_map[lno] == NULL)
	{
		perror("Map line malloc fail.");
		return (1);
	}
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		value = &line[i];
		world_map[lno][i] = ft_atoi(&line[i]);
		dprintf(2, "|%s=%d|", &line[i], world_map[lno][i]);
		i++;
	}
	dprintf(2, "\n");
	return (0);
}

int	**maploader(char *mapname)
{
	int		fd;
	int		map_height;
	int		**world_map;
	char	*line;
	int		lno;

	map_height = count_mapheight(mapname);
	dprintf(2, "mh: %d\n", map_height);
	if (map_height <= 0 || map_height > MAX_MAPHEIGHT)
	{
		perror("Error opening map file (height)");
		return (NULL);		
	}
	world_map = (int **)malloc(map_height * sizeof(int *));
	fd = open(mapname, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening map file");
		return (NULL);
	}
	lno = 0;
	while (lno <= MAX_MAPHEIGHT)
	{
		line = get_next_line(fd);
		if (!line || write_mapline(line, lno, world_map))
			break ;
		lno++;
	}
	close(fd);
	return (world_map);
}
