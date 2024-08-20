/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:24:31 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 13:27:56 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	heuristic(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	return (COST_STRAIGHT * (dx + dy) + (COST_DIAGONAL - 2 * COST_STRAIGHT)
		* min(dx, dy));
}

bool	is_in_bounds(int x, int y, t_data *data)
{
	return (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height);
}

bool	is_walkable(int x, int y, t_data *data)
{
	return (is_in_bounds(x, y, data) && data->world_map[y][x] == 0);
}

void	print_map(t_data *data)
{
	int y;
	int x;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
			printf("%d ", data->world_map[y][x]);
		printf("\n");
	}
}