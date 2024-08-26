/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:00:06 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/26 11:38:01 by mburakow         ###   ########.fr       */
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

	if (enemy->seen_player && enemy_is_alive(enemy))
	{
		if (enemy->state != ATTACKING)
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
 		else if (enemy->state == ATTACKING)
		{
			if (enemy->attacked == false && enemy->current_frame == 40 
				&& enemy->distance <= 1.6)
			{
				--data->player->hitpoints;
				printf("hitpoints: %d\n", data->player->hitpoints);
				enemy->attacked = true;
				if (data->player->hitpoints == 0)
					printf("GAME OVER MAN!!!\n");
			}					
		}
	}
}
