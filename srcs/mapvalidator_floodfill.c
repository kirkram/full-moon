/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator_floodfill.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 08:00:00 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 08:11:40 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	try_flood_fill(int pos_y, int pos_x, int **wmap, t_data *data)
{
	if (pos_x >= 0 && pos_x < data->map_width && pos_y >= 0
		&& pos_y < data->map_height)
	{
		return (flood_fill(pos_y, pos_x, wmap, data));
	}
	return (0);
}

static int	flood_compass_points(int pos_y, int pos_x, int **wmap, t_data *data)
{
	int	result;

	result = 0;
	result += try_flood_fill(pos_y, pos_x + 1, wmap, data);
	result += try_flood_fill(pos_y, pos_x - 1, wmap, data);
	result += try_flood_fill(pos_y + 1, pos_x, wmap, data);
	result += try_flood_fill(pos_y - 1, pos_x, wmap, data);
	result += try_flood_fill(pos_y + 1, pos_x + 1, wmap, data);
	result += try_flood_fill(pos_y - 1, pos_x - 1, wmap, data);
	result += try_flood_fill(pos_y + 1, pos_x - 1, wmap, data);
	result += try_flood_fill(pos_y - 1, pos_x + 1, wmap, data);
	if (result >= 1)
		result = 1;
	return (result);
}

int	flood_fill(int pos_y, int pos_x, int **wmap, t_data *data)
{
	if (wmap[pos_y][pos_x] == 1 || wmap[pos_y][pos_x] == 2)
		return (0);
	if (pos_y == 0 || pos_y == (data->map_height - 1) || pos_x == 0
		|| pos_x == data->map_width - 1 || wmap[pos_y][pos_x] == 9)
		return (1);
	wmap[pos_y][pos_x] = 2;
	return (flood_compass_points(pos_y, pos_x, wmap, data));
}
