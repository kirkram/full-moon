/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/18 14:24:21 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
static int	check_mapsquare(int pos_x, int pos_y, int **wmap)
{
	int	value;

	value = wmap[pos_y][pos_x];
	if (value == 48 || value == 49 || value == 50 || value == 78 || value == 69 
			|| value == 83 || value == 87) // go back
		return (0);
	else // wrong
		return (1);
}
*/
int flood_fill(int pos_x, int pos_y, int **wmap, t_data *data)
{ 
	int ret;
	int	val;

	ret = 0;
	val = wmap[pos_y][pos_x];
	// wall, visited, one of player starts: return
	if (val == 49 || val == 50 || val == 78 || val == 69 
			|| val == 83 || val == 87)
		return (0);
	// at the edge of the map, no empty squares
	else if (pos_y == 0 || pos_y == (data->map_height - 1) ||
		pos_x == 0 || pos_x == data->map_width - 1)
		return (1);
	// visited
	wmap[pos_y][pos_x] = 50;
	// check others
	ret += flood_fill(pos_x + 1, pos_y, wmap, data);
	ret += flood_fill(pos_x - 1, pos_y, wmap, data);
	ret += flood_fill(pos_x, pos_y + 1, wmap, data);
	ret += flood_fill(pos_x, pos_y - 1, wmap, data);
	return (ret);
}

int	validate_map(int **world_map, t_data *data)
{
	int	**test_map;

	test_map = copy_2d_int(world_map, data->map_height, data->map_width);
	if (flood_fill(data->startpos[0], data->startpos[1], test_map, data))
	{
		free_2d_int(world_map);
		free_2d_int(test_map);
		return (1);
	}
	else
		return (0);	
}