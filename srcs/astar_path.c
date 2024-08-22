/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:36:45 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/22 23:02:26 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

void	initialize_closed_set(t_astar *context, t_data *data)
{
	int	i;

	context->closed_set = (int **)ft_calloc(data->map_height, sizeof(int *));
	if (!context->closed_set)
		error_a_star(context, data);
	i = -1;
	while (++i < data->map_height)
	{
		context->closed_set[i] = (int *)ft_calloc(data->map_width, sizeof(int));
		if (!context->closed_set[i])
			error_a_star(context, data);
	}
	return ;
}

static void	retrace(int count, t_node *current, t_route *route)
{
	while (current->parent && count >= 0)
	{
		count--;
		route->coords[count].x = current->x;
		route->coords[count].y = current->y;
		// printf("C: %d x: %d y: %d\n", count, route->coords[count].x,
		//	route->coords[count].y);
		current = current->parent;
	}
}

t_route	*reconstruct_path(t_node *end_node)
{
	t_node	*current;
	t_route	*route;

	current = end_node;
	route = (t_route *)malloc(sizeof(t_route));
	route->size = 0;
	while (current->parent)
	{
		// printf("size: %d x: %d y: %d\n", route->size, current->x, current->y);
		route->size++;
		current = current->parent;
	}
	route->coords = (t_coord *)malloc(sizeof(t_coord) * (route->size + 1));
	route->coords[route->size].x = -1;
	route->coords[route->size].y = -1;
	current = end_node;
	retrace(route->size, current, route);
	// printf("Route length: %d\n", route->size);
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
