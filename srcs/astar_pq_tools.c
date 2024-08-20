/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_pq_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:18:07 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 13:23:20 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

void	print_node(t_node *node)
{
	printf("PQ x:%d\ty:%d\tg:%d\th:%d\tf:%d", node->x, node->y, node->g,
		node->h, node->f);
	if (node->parent)
	{
		printf("\tpx:%d\tpy:%d", node->parent->x, node->parent->y);
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

t_priorityqueue	*pq_create(int capacity)
{
	t_priorityqueue	*pq;

	pq = (t_priorityqueue *)malloc(sizeof(t_priorityqueue));
	/*
	if (!pq)
		free_all_and_quit(data);
	*/
	pq->nodes = (t_node *)malloc(capacity * sizeof(t_node));
	pq->size = 0;
	pq->capacity = capacity;
	return (pq);
}

t_node	*create_node(int x, int y, int g, int h, t_node *parent)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	node->x = x;
	node->y = y;
	node->g = g;
	node->h = h;
	node->f = g + h;
	node->parent = parent;
	return (node);
}