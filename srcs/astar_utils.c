/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:24:31 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/31 15:21:41 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

int	heuristic(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	return (COST_STRAIGHT * (dx + dy) + \
		(COST_DIAGONAL - 2 * COST_STRAIGHT) * min(dx, dy));
}

bool	is_in_bounds(int x, int y, t_data *data)
{
	return (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height);
}

bool	is_walkable(int x, int y, t_data *data)
{
	return (is_in_bounds(x, y, data) && (data->world_map[y][x] == 0
		|| data->world_map[y][x] == 6));
}

void	print_map(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
			printf("%d ", data->world_map[y][x]);
		printf("\n");
	}
}

int	process_neighbors_newg(t_node *current, int i)
{
	if (i < 4)
		return (current->g + COST_STRAIGHT);
	else
		return (current->g + COST_DIAGONAL);
}
