/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:15:56 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 11:08:25 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

int	node_is_target(t_node *current, t_coord end_pos,
		t_astar *context)
{
	if (current->x == end_pos.x && current->y == end_pos.y)
		return (1);
	context->closed_set[current->y][current->x] = 1;
	return (0);
}

void	process_neighbors(t_node *current, t_astar *context, t_data *data,
		t_coord end_pos)
{
	int		i;
	t_coord	new_coord;
	int		new_g;
	t_node	*neighbor;

	i = -1;
	while (++i < 8)
	{
		new_coord.x = current->x + context->directions[i][0];
		new_coord.y = current->y + context->directions[i][1];
		if (is_in_bounds(new_coord.x, new_coord.y, data)
			&& !context->closed_set[new_coord.y][new_coord.x]
			&& is_walkable(new_coord.x, new_coord.y, data))
		{
			new_g = process_neighbors_newg(current, i);
			neighbor = create_node(new_coord, new_g, heuristic(new_coord.x,
						new_coord.y, end_pos.x, end_pos.y), current);
			if (!neighbor)
				error_a_star(context, data);
			pq_push(context->open_set, neighbor, context, data);
			free(neighbor);
			neighbor = NULL;
		}
	}
}

int	process_current_node(t_node *current, t_coord end_pos, t_astar *context,
		t_data *data)
{
	if (node_is_target(current, end_pos, context))
		return (1);
	process_neighbors(current, context, data, end_pos);
	return (0);
}

t_route	*run_a_star(t_astar *context, t_coord end_pos, t_data *data)
{
	t_node	*current;

	current = NULL;
	while (context->open_set->size > 0)
	{
		current = pq_pop(context->open_set, context, data);
		add_node_to_list(context->closed_list, current);
		if (process_current_node(current, end_pos, context, data))
		{
			context->route = reconstruct_path(current);
			return (context->route);
		}
	}
	return (NULL);
}

t_route	*a_star(t_coord start_pos, t_coord end_pos, t_data *data)
{
	t_astar	*context;
	t_route	*route;

	context = initialize_a_star(start_pos, data);
	route = run_a_star(context, end_pos, data);
	cleanup_a_star(context, data);
	return (route);
}
