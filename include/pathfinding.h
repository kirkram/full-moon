/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:15:50 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/19 19:55:30 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define COST_STRAIGHT 10
#define COST_DIAGONAL 14

typedef struct s_node
{
    int 			x; 
	int				y;
    int 			g;
	int				h;
    int 			f;
    struct s_node*	parent;
} t_node;

typedef struct s_priorityqueue
{
    t_node	*nodes;
    int		size;
	int		capacity;
} t_priorityqueue;