/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_pq_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:18:07 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 11:11:34 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

void	print_node(t_node *node)
{
	printf("PQ \tx:%d\ty:%d\tg:%d\th:%d\tf:%d\ta:%p\tc:%p", node->x, node->y,
		node->g, node->h, node->f, (void *)node, (void *)&node);
	if (node->parent)
	{
		printf("\tpx:%d\tpy:%d\tpa:%p\tpc:%p", node->parent->x, node->parent->y,
			(void *)node, (void *)&node);
	}
	printf("\n");
}

void	print_priority_queue(t_priorityqueue *pq)
{
	int	i;

	i = -1;
	while (++i < pq->size)
		print_node(&pq->nodes[i]);
}

t_node	*peek(t_priorityqueue *pq)
{
	if (!pq->size)
	{
		printf("peek: Priority queue is empty\n");
		return (NULL);
	}
	return (&pq->nodes[0]);
}

void	pq_create(int capacity, t_astar *context, t_data *data)
{
	context->open_set = (t_priorityqueue *)malloc(sizeof(t_priorityqueue));
	if (!context->open_set)
		error_a_star(context, data);
	context->open_set->nodes = (t_node *)malloc(capacity * sizeof(t_node));
	if (!context->open_set->nodes)
		error_a_star(context, data);
	context->open_set->size = 0;
	context->open_set->capacity = capacity;
	return ;
}

t_node	*create_node(t_coord new, int g, int h, t_node *parent)
{
	static uint32_t	i = 0;
	t_node			*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->x = new.x;
	node->y = new.y;
	node->g = g;
	node->h = h;
	node->f = g + h;
	node->parent = parent;
	node->id = i;
	i++;
	return (node);
}
