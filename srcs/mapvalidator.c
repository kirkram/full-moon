/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/17 14:51:35 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_mapsquare(int pos_x, int pos_y, int **wmap)
{
	if (wmap[pos_y][pos_x] >= 0 && wmap[pos_y][pos_x] <= 5)
		return (0);
	else
		return (1);
}

int flood_fill(int pos_x, int pos_y, int **wmap, t_data *data)
{ 
	int ret;

	ret = 0;
	if(wmap[pos_y][pos_x] != 0 && wmap[pos_y][pos_x] != 5)
		return;
	else if (pos_y == 0 || pos_y == (data->map_height - 1) ||
		pos_x == 0 || pos_x == data->map_width - 1)
		return (1);
	else
	{
		ret = check_mapsquare(pos_x + 1, pos_y, wmap);
		ret = check_mapsquare(pos_x - 1, pos_y, wmap);
		ret = check_mapsquare(pos_x, pos_y + 1, wmap);
		ret = check_mapsquare(pos_x, pos_y - 1, wmap);
	}
	flood_fill(pos_x + 1, pos_y, wmap, data);
	flood_fill(pos_x - 1, pos_y, wmap, data);
	flood_fill(pos_x, pos_y + 1, wmap, data);
	flood_fill(pos_x, pos_y - 1, wmap, data);
	return (ret);
}

int	validate_map(int **world_map, t_data *data)
{
	if (flood_fill(data->startpos[0], data->startpos[1], world_map, data))
		return (1);
	else
		return (0);	
}