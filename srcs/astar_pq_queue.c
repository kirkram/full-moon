/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_pq_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:48:56 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 18:11:42 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pathfinding.h"

static void	pq_swap(t_node *a, t_node *b)
{
	t_node	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	heapify_up(t_priorityqueue *pq, int i)
{
	if (i && pq->nodes[(i - 1) / 2].f > pq->nodes[i].f)
	{
		pq_swap(&pq->nodes[(i - 1) / 2], &pq->nodes[i]);
		heapify_up(pq, (i - 1) / 2);
	}
}

static void	heapify_down(t_priorityqueue *pq, int i)
{
	int	smallest;
	int	left;
	int	right;

	smallest = i;
	left = 2 * i + 1;
	right = 2 * i + 2;
	if (left < pq->size && pq->nodes[left].f < pq->nodes[smallest].f)
		smallest = left;
	if (right < pq->size && pq->nodes[right].f < pq->nodes[smallest].f)
		smallest = right;
	if (smallest != i)
	{
		pq_swap(&pq->nodes[i], &pq->nodes[smallest]);
		heapify_down(pq, smallest);
	}
}

void	pq_push(t_priorityqueue *pq, t_node *node, t_astar *context, t_data *data)
{
	if (context->open_set->size >= pq->capacity)
	{
		pq->nodes = (t_node *)ft_realloc(pq->nodes, pq->capacity * sizeof(t_node), 
			pq->capacity * 2 * sizeof(t_node));
		if (!pq->nodes)
			error_a_star(context, data);
		pq->capacity *= 2;
	}
	pq->nodes[pq->size++] = *node;
	heapify_up(pq, pq->size - 1);
}

t_node	*pq_pop(t_priorityqueue *pq, t_astar *context, t_data *data)
{
	t_node	*result;

	if (!pq->size)
	{
		printf("pq_pop: Priority queue is empty\n");
		return (NULL);
	}
	result = (t_node *)malloc(sizeof(t_node));
	if (!result)
		error_a_star(context, data);
	*result = pq->nodes[0];
	pq->nodes[0] = pq->nodes[--pq->size];
	heapify_down(pq, 0);
	return (result);
}
