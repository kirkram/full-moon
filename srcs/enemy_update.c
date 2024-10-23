/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:00:06 by mburakow          #+#    #+#             */
/*   Updated: 2024/10/23 11:41:03 by klukiano         ###   ########.fr       */
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

static void	attack_state(t_enemy *enemy, t_data *data)
{
	if (enemy->attacked == false
		&& enemy->distance <= 1.6 && enemy->state == ATTACKING
		&& data->player->hitpoints > 0)
	{
		--data->player->hitpoints;
		printf("Player hitpoints: %d\n", data->player->hitpoints);
		enemy->attacked = true;
	}
	else if (enemy->distance > 1.6 && enemy->state != TAKINGDMG)
	{
		// printf("Enemy state is now IDLE\n");
		enemy->state = IDLE;
	}
}

void	update_enemy(t_enemy *enemy, t_data *data)
{
	t_coord	player_pos;
	t_coord	enemy_pos;

	if (enemy->seen_player && enemy_is_alive(enemy))
	{
		if (enemy->state != ATTACKING && enemy->state != TAKINGDMG)
		{
			enemy->state = WALKING;
			player_pos = get_player_position(data);
			enemy_pos = get_enemy_position(enemy);
			if (enemy->route == NULL)
				initialize_enemy_route(enemy, player_pos, enemy_pos, data);
			else if (has_reached_target(enemy))
				update_enemy_target(enemy, player_pos, enemy_pos, data);
			move_enemy(data, enemy);
		}
		else if (enemy->state == ATTACKING)
		{
			attack_state(enemy, data);
		}
	}
}
