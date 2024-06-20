/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:36:38 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/20 16:20:19 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_valid_map(t_data *data, int ac, char **av)
{
	char	*mappath;
	data->startpos_x = 0;
	data->startpos_y = 0;
	if (ac == 1)
		mappath = "./maps/default.cub";
	else if (ac == 2)
		mappath = ft_strjoin("./maps/", av[1]);
	else
		exit(ft_error("Wrong argument count.", 25));
	data->world_map = load_map(mappath, data);
	if (validate_map(data->world_map, data))
		exit(ft_error("Map error*", 12));
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
	load_valid_map(&data, ac, av);
	init_and_draw(&data);
	free_2d_int(data.world_map, data.map_height);
	return (0);
}
