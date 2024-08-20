/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:36:45 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 13:46:38 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

int	**initialize_closed_set(t_data *data)
{
	int	i;
	int	**closed_set;

	// change forbidden functions
	closed_set = (int **)calloc(data->map_height, sizeof(int *));
	// malloc protect
	i = -1;
	while (++i < data->map_height)
		closed_set[i] = (int *)calloc(data->map_width, sizeof(int));
	// malloc protect
	return (closed_set);
}

static void	retrace(int count, t_node *current, t_route *route)
{
	while (current && count >= 1)
	{
		count--;
		route->coords[count].x = current->x;
		route->coords[count].y = current->y;
		printf("C: %d x: %d y: %d\n", count, route->coords[count].x,
			route->coords[count].y);
		current = current->parent;
		if (current->parent == NULL)
			break ;
	}
}

t_route	*reconstruct_path(t_node *end_node)
{
	t_node	*current;
	t_route	*route;
	int		count;

	current = end_node;
	route = (t_route *)malloc(sizeof(t_route));
	route->size = -1;
	while (current)
	{
		route->size++;
		current = current->parent;
	}
	route->coords = (t_coord *)malloc(sizeof(t_coord) * (route->size + 1));
	route->coords[route->size].x = -1;
	route->coords[route->size].y = -1;
	current = end_node;
	count = route->size;
	retrace(count, current, route);
	return (route);
}

void	set_directions(int directions[8][2])
{
	directions[0][0] = 0;
	directions[0][1] = 1;
	directions[1][0] = 1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = -1;
	directions[3][0] = -1;
	directions[3][1] = 0;
	directions[4][0] = 1;
	directions[4][1] = 1;
	directions[5][0] = 1;
	directions[5][1] = -1;
	directions[6][0] = -1;
	directions[6][1] = -1;
	directions[7][0] = -1;
	directions[7][1] = 1;
}