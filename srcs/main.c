/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:36:38 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/26 12:58:58 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_valid_map(t_data *data, int ac, char **av)
{

	if (ac == 1)
		data->map_path = ft_strjoin("./maps/", "default.cub");
	else if (ac == 2)
		data->map_path = ft_strdup(av[1]);
	else
		exit(ft_error("Wrong argument count.", 25));
	load_map(data);
	if (validate_map(data->world_map, data))
		map_validation_error("Error: map validation", data->map_height, NULL, data);
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
	load_valid_map(&data, ac, av);
	init_and_draw(&data);

	int i = -1;
	while (data.nsew_path && data.txtrs && ++i < TEXTURES_AMOUNT)
	{
		free(data.nsew_path[i]);
	}
	free(data.txtrs);
	free(data.nsew_path);
	free_2d_int(data.world_map, data.map_height);
	
	return (0);
}
