/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_init_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:44:39 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 18:47:57 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

t_astar	*initialize_a_star(t_coord start_pos, t_data *data)
{
	t_astar	*context;

	context = (t_astar *)malloc(sizeof(t_astar));
	if (!context)
		free_all_and_quit(data, "error a star", 32);
	set_directions(context->directions);
	pq_create(200, context, data);
	initialize_closed_set(context, data);
	context->start_node = create_node(start_pos, 0, 0, NULL);
	if (!context->start_node)
		error_a_star(context, data);
	pq_push(context->open_set, context->start_node, context, data);
	return (context);
}

void	cleanup_a_star(t_astar *context, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		free(context->closed_set[i]);
		i++;
	}
	free(context->closed_set);
	free(context->open_set->nodes);
	free(context->open_set);
	free(context);
}

void	error_a_star(t_astar *context, t_data *data)
{
	int i;

	i = 0;
	while (i < data->map_height)
	{
		if (context->closed_set[i])
			free(context->closed_set[i]);
		i++;
	}
	if (context->closed_set)
		free(context->closed_set);
	if (context->open_set->nodes)
		free(context->open_set->nodes);
	if (context->open_set)
		free(context->open_set);
	if (context)
		free(context);
	free_all_and_quit(data, "a star error", 32);
}