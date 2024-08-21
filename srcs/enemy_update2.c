/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:16:01 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 15:25:36 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_new_target(t_enemy *enemy)
{
	enemy->x_target = enemy->route->coords[0].x + 0.5;
	enemy->y_target = enemy->route->coords[0].y + 0.5;
}

void	update_enemy_target(t_enemy *enemy, t_coord player_pos,
		t_coord enemy_pos, t_data *data)
{
	if (enemy->route->coords[0].x == -1)
	{
		printf("Route finished.\n");
		free(enemy->route);
		enemy->route = NULL;
		if (enemy->distance > 1.0)
			enemy->route = a_star(enemy_pos, player_pos, data);
	}
	else
	{
		set_new_target(enemy);
		calculate_enemy_angle(enemy);
		printf("New waypoint: x %f y %f\n", enemy->x_target, enemy->y_target);
		printf("Position: x %f y %f\n", enemy->x_pos, enemy->y_pos);
		// log_route_points(enemy);
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
	printf("I saw the player!\n");
	enemy->state = WALKING;
	enemy->route = a_star(enemy_pos, player_pos, data);
	// log_route_points(enemy);
}

void	log_route_points(t_enemy *enemy)
{
	int	i;

	i = 0;
	while (enemy->route->coords[i].x != -1)
	{
		printf("route point %d: x %d y %d\n", i, enemy->route->coords[i].x,
			enemy->route->coords[i].y);
		++i;
	}
}