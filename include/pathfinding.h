/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:15:50 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 13:41:53 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define COST_STRAIGHT 10
#define COST_DIAGONAL 14

typedef struct s_node 
{
    int x; // square x coord
	int y;  // square y coord
	int g; // cost to move here
	int h; // heuristic: estimated cost to move to target
	int f; // g + h : total cost
    struct s_node* parent; // fom here we got to this square
} t_node;

typedef struct s_priorityqueue
{
    t_node* nodes;
    int size;
	int capacity;
} t_priorityqueue;

// pathfinding internal functions
int				**initialize_closed_set(t_data *data);
t_priorityqueue	*pq_create(int capacity);
t_node			*create_node(int x, int y, int g, int h, t_node *parent);
void			set_directions(int directions[8][2]);
void			pq_push(t_priorityqueue *pq, t_node *node);
t_node*			pq_pop(t_priorityqueue *pq);
t_node			*peek(t_priorityqueue *pq);
int				min(int a, int b);
int				heuristic(int x1, int y1, int x2, int y2);
bool			is_in_bounds(int x, int y, t_data *data);
bool			is_walkable(int x, int y, t_data *data);
t_route			*reconstruct_path(t_node *end_node);

// pathfinding (debug) tools
void			print_map(t_data *data);
void			print_node(t_node *node);
void			print_priority_queue(t_priorityqueue *pq);

