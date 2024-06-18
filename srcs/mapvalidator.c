/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/18 20:54:36 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int flood_fill(int pos_y, int pos_x, int **wmap, t_data *data)
{ 
	int ret;

	ret = 0;
	if (wmap[pos_y][pos_x] == 1 || wmap[pos_y][pos_x] == 2)
		return (0);
	if (pos_y == 0 || pos_y == (data->map_height - 1) ||
		pos_x == 0 || pos_x == data->map_width - 1)
		return (1);
	wmap[pos_y][pos_x] = 2;
	if (pos_x < data->map_width - 1)
		ret += flood_fill(pos_y, pos_x + 1, wmap, data);
	if (pos_x > 0)
		ret += flood_fill(pos_y, pos_x - 1, wmap, data);
	if (pos_y < data->map_height - 1)
		ret += flood_fill(pos_y + 1, pos_x, wmap, data);
	if (pos_y > 0)
		ret += flood_fill(pos_y - 1, pos_x, wmap, data);
	if (pos_x < data->map_width - 1 && pos_y < data->map_height - 1)
		ret += flood_fill(pos_y + 1, pos_x + 1, wmap, data);
	if (pos_x > 0 && pos_y > 0)
		ret += flood_fill(pos_y - 1, pos_x - 1, wmap, data);
	if (pos_y < data->map_height - 1 && pos_x > 0)
		ret += flood_fill(pos_y + 1, pos_x - 1, wmap, data);
	if (pos_x < data->map_width - 1 && pos_y > 0)
		ret += flood_fill(pos_y - 1, pos_x + 1, wmap, data);
	return (ret);
}

int	validate_map(int **world_map, t_data *data)
{
	int	**test_map;

	test_map = copy_2d_int(world_map, data->map_height, data->map_width);
	printf("start y: %d\n", data->startpos_y);
	printf("start x: %d\n", data->startpos_x);
	printf("val at player pos: %d\n", world_map[data->startpos_y][data->startpos_x]);
	if (flood_fill(data->startpos_y, data->startpos_x, world_map, data))
	{
		free_2d_int(test_map, data->map_height);
		printf("Map validation failed\n");
		return (0);
	}
	else
	{
		free_2d_int(test_map, data->map_height);
		return (0);
	}
}