/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 08:10:09 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_mapsquare(int value)
{
	if (value == '0' || value == '1' || value == '4' || value == ' '
		|| value == '5')
		return (0);
	else if (value == 'N' || value == 'E' || value == 'S' || value == 'W')
		return (0);
	else
		return (1);
}

static void	validate_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_AMOUNT && data->nsew_path)
	{
		if (i < 4)
		{
			if (access(data->nsew_path[i], F_OK))
				map_validation_error("Error: missing main NSEW texture",
					data->map_height, NULL, data);
		}
	}
}

static int	validate_map_integrity(int **world_map, t_data *data)
{
	int	**test_map;

	test_map = copy_2d_int(world_map, data->map_height, data->map_width);
	if (flood_fill(data->startpos_y, data->startpos_x, test_map, data))
	{
		free_2d_int(test_map, data->map_height);
		return (1);
	}
	else
	{
		free_2d_int(test_map, data->map_height);
		return (0);
	}
}

int	validate_map(int **world_map, t_data *data)
{
	if (data->startpos_x == 0 || data->startpos_y == 0)
		map_validation_error("Error: no player starting point",
			data->map_height, NULL, data);
	validate_textures(data);
	return (validate_map_integrity(world_map, data));
}
