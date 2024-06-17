/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapvalidator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:02:18 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/17 11:38:23 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int wall = -1;

// If not a wall, check that x +-1 and y +-1 not out of bounds
int flood_fill(int pos_x, int pos_y, int **wmap)
{ 
	int ret;

	ret = 0;
	if(wmap[pos_y][pos_x] != 0 && wmap[pos_y][pos_x] != 5) // if it's not floor go back
		return;
	// a[pos_x][pos_y] = color; // mark the point so that I know if I passed through it.  
	// might need duplication
	flood_fill(pos_x + 1, pos_y, wmap);  // then i can either go south
	flood_fill(pos_x - 1, pos_y, wmap);  // or north
	flood_fill(pos_x, pos_y + 1, wmap);  // or east
	flood_fill(pos_x, pos_y - 1, wmap);  // or west
   return;
}

int	validate_map(int **world_map, t_data *data)
{
	if (flood_fill(data->startpos[0], data->startpos[1], world_map))
		return (1);
	else
		return (0);	
}