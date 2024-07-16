/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:36:38 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/16 22:56:58 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_valid_map(t_data *data, int ac, char **av)
{
	if (ac == 1)
		data->map_path = "./maps/default.cub";
	else if (ac == 2)
		data->map_path = av[1];
	else
		exit(ft_error("Wrong argument count.", 25));
	load_map(data);
	if (validate_map(data->world_map, data))
		map_validation_error("Error: map validation", data->map_height, NULL,
			data);
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
	init_map_data(&data);
	init_player_data(&player);
	load_valid_map(&data, ac, av);
	init_and_draw(&data);
	free_all_and_quit(&data, "Bye!", 0);
	return (0);
}
