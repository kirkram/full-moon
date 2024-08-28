/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_checked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:04:55 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/28 13:39:00 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

void	create_node_list(int capacity, t_astar *context, t_data *data) 
{
	context->closed_list = (t_nodelist *)malloc(sizeof(t_nodelist));
	if (!context->closed_list)
		error_a_star(context, data);
	context->closed_list->nodes = (t_node **)malloc(capacity * sizeof(t_node *));
	if (!context->closed_list->nodes)
		error_a_star(context, data);
	context->closed_list->size = 0;
	context->closed_list->capacity = capacity;
}

void add_node_to_list(t_nodelist *list, t_node *node) 
{
    if (list->size >= list->capacity) 
	{
        list->capacity *= 2;
        list->nodes = (t_node **)ft_realloc(list->nodes, list->capacity * sizeof(t_node *));
    }
    list->nodes[list->size++] = node;
}

void free_node_list(t_nodelist *list) 
{
	int	i;

	i = -1;
    while (++i < list->size) 
	{
        free(list->nodes[i]);
    }
    free(list->nodes);
	list->nodes = NULL;
    free(list);
	list = NULL;
}