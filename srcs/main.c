/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:36:38 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/18 14:01:18 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	copy_example_map(t_data *data)
{
	int	**world_map;

	world_map = load_map("./maps/default.cub", data);
	if (validate_map(world_map, data))
		return (ft_error("Map error*", 12));
	data->world_map = copy_2d_int(world_map, data->map_height, data->map_width);
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
