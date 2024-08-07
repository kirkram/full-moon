/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:15:50 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/07 19:18:16 by mburakow         ###   ########.fr       */
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

/*
typedef struct s_data
{
    int **world_map;
    int map_width;
	int map_height;
} t_data;
*/