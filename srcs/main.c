/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:36:38 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/27 16:55:41 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	nines_to_ones(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->world_map[y][x] == 9)
				data->world_map[y][x] = 1;
		}
	}
}

int	load_valid_map(t_data *data, int ac, char **av)
{
	if (ac == 1)
		data->map_path = "./maps/default.cub";
	else if (ac == 2)
		data->map_path = av[1];
	else
		exit(ft_error("Error\nWrong argument count.", 25));
	load_map(data);
	if (validate_map(data->world_map, data))
		free_all_and_quit(data, "Error\nMap validation error.\n", 32);
	nines_to_ones(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_player	player;
	t_ray		ray;

	if (FOV <= 0 || RESOLUTION <= 0)
		return (ft_error("Error\nFOV / RESOLUTION can't be 0 or negative", 44));
	data.player = &player;
	data.ray = &ray;
	init_map_data(&data);
	init_player_data(&player);
	load_valid_map(&data, ac, av);
	init_and_draw(&data);
	free_all_and_quit(&data, "Bye!", 0);
	return (0);
}
