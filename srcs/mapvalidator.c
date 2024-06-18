/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/18 19:30:36 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int flood_fill(int pos_y, int pos_x, int **wmap, t_data *data)
{ 
	int ret;
	int	val;

	ret = 0;
	val = wmap[pos_y][pos_x];
	printf("%d:%d\n", pos_y, pos_x);
	if (val == 1)
	{
		printf("Hit a wall at %d:%d.\n", pos_y, pos_x);
		return (0);
	}
	if (val == 2)
	{
		printf("Checked already %d:%d.\n", pos_y, pos_x);
		return (0);
	}
	if (pos_y == 0 || pos_y == (data->map_height - 1) ||
		pos_x == 0 || pos_x == data->map_width - 1)
	{
		printf("Reached edge at %d:%d.\n", pos_y, pos_x);
		return (1); // out of bounds
	}
	wmap[pos_y][pos_x] = 2;
	// main
	if (pos_x < data->map_width - 2)
		ret += flood_fill(pos_y, pos_x + 1, wmap, data);
	if (pos_x > 0)
		ret += flood_fill(pos_y, pos_x - 1, wmap, data);
	if (pos_y < data->map_height - 2)
		ret += flood_fill(pos_y + 1, pos_x, wmap, data);
	if (pos_y > 0)
		ret += flood_fill(pos_y - 1, pos_x, wmap, data);
	// diagonal
	if (pos_x < data->map_width - 2 && pos_y < data->map_height - 2)
		ret += flood_fill(pos_y + 1, pos_x + 1, wmap, data);
	if (pos_x > 0 && pos_y > 0)
		ret += flood_fill(pos_y - 1, pos_x - 1, wmap, data);
	if (pos_y < data->map_height - 2 && pos_x > 0)
		ret += flood_fill(pos_y + 1, pos_x - 1, wmap, data);
	if (pos_x < data->map_width - 1 && pos_y > 0)
		ret += flood_fill(pos_y - 1, pos_x + 1, wmap, data);
	print_2d_int(wmap, data->map_height, data->map_width);
	return (ret);
}

int	validate_map(int **world_map, t_data *data)
{
	//int	**test_map;

	//test_map = copy_2d_int(world_map, data->map_height, data->map_width);
	print_2d_int(world_map, data->map_height, data->map_width);
	printf("start y: %d\n", data->startpos[0]);
	printf("start x: %d\n", data->startpos[1]);
	printf("val at player pos: %d\n", world_map[data->startpos[0]][data->startpos[1]]);
	if (flood_fill(data->startpos[0], data->startpos[1], world_map, data))
	{
		//free_2d_int(world_map);
		//free_2d_int(test_map);
		printf("Map validation failed\n");
		return (0);
	}
	else
		return (0);	
}