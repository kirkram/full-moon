/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:36:38 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/17 18:19:16 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	copy_example_map(t_data *data)
{
	int	x;
	int	y;
	int	**world_map;
	int	ret;

	world_map = load_map("./maps/default.cub", data);
	ret = validate_map(world_map, data);
	if (ret)
	{
		dprintf(2, "ret was: %d", ret);
		return (ft_error("Map error*", 12));
	}	
	data->world_map = malloc(data->map_height * sizeof(int *));
	if (!data->world_map)
		return (ft_error("Malloc error on int*", 22));
	y = -1;
	while (++y < data->map_height)
	{
		data->world_map[y] = malloc(MAPWIDTH * sizeof(int));
		if (!data->world_map[y])
			return (ft_error("Malloc error on int", 22));
	}
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < MAPWIDTH)
		{
			data->world_map[y][x] = world_map[y][x];
		}
	}
	free_2d_int(world_map);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_player	player;
	t_ray		ray;

	(void)ac;
	(void)av;
	if (FOV <= 0 || RESOLUTION <= 0)
		return (ft_error("FOV / RESOLUTION can't be 0 or negative", 44));
	data.player = &player;
	data.ray = &ray;
	copy_example_map(&data);
	init_and_draw(&data);
	free_2d_int(data.world_map);
	return (0);
}
