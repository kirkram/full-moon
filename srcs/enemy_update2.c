/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:16:01 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/19 17:08:51 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_player_moved(t_enemy *enemy, t_coord player_pos)
{
	if (enemy->route->coords[enemy->route->size - 1].x != player_pos.x 
		|| enemy->route->coords[enemy->route->size - 1].y != player_pos.y)
	{	
		return (1);
	}
	return (0);
}

static void	set_new_target(t_enemy *enemy)
{
	enemy->x_target = enemy->route->coords[0].x + 0.5;
	enemy->y_target = enemy->route->coords[0].y + 0.5;
}

void	update_enemy_target(t_enemy *enemy, t_coord player_pos,
		t_coord enemy_pos, t_data *data)
{
	if (has_player_moved(enemy, player_pos) || enemy->route->coords[0].x == -1)
	{
		free(enemy->route->coords);
		free(enemy->route);
		enemy->route = NULL;
		if (enemy->distance > 1.0)
			enemy->route = a_star(enemy_pos, player_pos, data);
	}
	else
	{
		set_new_target(enemy);
		calculate_enemy_angle(enemy);
		step_route(enemy);
	}
}

int	has_reached_target(t_enemy *enemy)
{
	return (is_equal(enemy->x_pos, enemy->x_target) && is_equal(enemy->y_pos,
			enemy->y_target));
}

void	initialize_enemy_route(t_enemy *enemy, t_coord player_pos,
		t_coord enemy_pos, t_data *data)
{
	double	now;

	now = mlx_get_time();
	if (now - enemy->last_route > 0.5 || is_equal(enemy->last_route, 0.0))
	{
		printf("Enemy state is now WALKING\n");
		enemy->state = WALKING;
		enemy->last_route = now;
		enemy->route = a_star(enemy_pos, player_pos, data);
	}
}
