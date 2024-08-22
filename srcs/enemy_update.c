/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:00:06 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/22 22:46:48 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_route(t_enemy *enemy)
{
	int	i;

	i = 0;
	while (enemy->route->coords[i].x != -1)
	{
		enemy->route->coords[i].x = enemy->route->coords[i + 1].x;
		enemy->route->coords[i].y = enemy->route->coords[i + 1].y;
		i++;
	}
	enemy->route->size -= 1;
}

static t_coord	get_player_position(t_data *data)
{
	t_coord	player_pos;

	player_pos.x = data->player->x_pos;
	player_pos.y = data->player->y_pos;
	return (player_pos);
}

static t_coord	get_enemy_position(t_enemy *enemy)
{
	t_coord	enemy_pos;

	enemy_pos.x = enemy->x_pos;
	enemy_pos.y = enemy->y_pos;
	return (enemy_pos);
}

void	update_enemy(t_enemy *enemy, t_data *data)
{
	t_coord	player_pos;
	t_coord	enemy_pos;

	if (enemy->attack && enemy_is_alive(enemy))
	{
		player_pos = get_player_position(data);
		enemy_pos = get_enemy_position(enemy);
		if (enemy->route == NULL)
		{
			initialize_enemy_route(enemy, player_pos, enemy_pos, data);
		}
		else if (has_reached_target(enemy))
		{
			update_enemy_target(enemy, player_pos, enemy_pos, data);
		}
		move_enemy(data, enemy);
	}
}

/*
original:

void	update_enemy(t_enemy *enemy, t_data *data)
{
	int		i;
	t_coord	player_pos;
	t_coord	enemy_pos;

	if (enemy->attack && enemy_is_alive(enemy))
	{
		player_pos.x = data->player->x_pos;
		player_pos.y = data->player->y_pos;
		enemy_pos.x = enemy->x_pos;
		enemy_pos.y = enemy->y_pos;
		if (enemy->route == NULL)
		{
			printf("I saw the player!\n");
			enemy->state = WALKING;
			enemy->route = a_star(enemy_pos, player_pos, data);
			i = 0;
			while (enemy->route->coords[i].x != -1)
			{
				printf("route point %d: x %d y %d\n", i,
					enemy->route->coords[i].x, enemy->route->coords[i].y);
				++i;
			}
			return ;
		}
		if (is_equal(enemy->x_pos, enemy->x_target) && is_equal(enemy->y_pos,
				enemy->y_target))
		{
			printf("Getting new route point.\n");
			if (enemy->route->coords[0].x == -1)
			{
				printf("Route finished.\n");
				free(enemy->route);
				enemy->route = NULL;
				if (enemy->distance > 1.0)
					enemy->route = a_star(enemy_pos, player_pos, data);
				return ;
			}
			else
			{
				enemy->x_target = enemy->route->coords[0].x + 0.5;
				enemy->y_target = enemy->route->coords[0].y + 0.5;
				calculate_enemy_angle(enemy);
				printf("New waypoint: x %f y %f\n", enemy->x_target,
					enemy->y_target);
				printf("Position: x %f y %f\n", enemy->x_pos, enemy->y_pos);
				i = 0;
				while (enemy->route->coords[i].x != -1)
				{
					printf("route point %d: x %d y %d\n", i,
						enemy->route->coords[i].x, enemy->route->coords[i].y);
					++i;
				}
				step_route(enemy);
			}
		}
		// printf("Moving enemy.\n");
		move_enemy(data, enemy);
	}
}
*/