/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:55:20 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 14:29:05 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_position_valid(t_data *data, float y, float x)
{
	return (x >= 0 && x < data->map_width && y >= 0 && y < data->map_height
		&& data->world_map[(int)y][(int)x] != 1
		&& data->world_map[(int)y][(int)x] != 4);
}

void	move_enemy_position(t_data *data, t_enemy *enemy, t_fcoord direction,
		float delta_time)
{
	float	move_x;
	float	move_y;

	move_x = direction.x * ENEMYSPEED * delta_time + enemy->x_pos;
	move_y = direction.y * ENEMYSPEED * delta_time + enemy->y_pos;
	if ((direction.x > 0 && move_x > enemy->x_target) || (direction.x < 0
			&& move_x < enemy->x_target))
		move_x = enemy->x_target;
	if ((direction.y > 0 && move_y > enemy->y_target) || (direction.y < 0
			&& move_y < enemy->y_target))
		move_y = enemy->y_target;
	if (is_position_valid(data, enemy->y_pos, move_x))
		enemy->x_pos = move_x;
	if (is_position_valid(data, move_y, enemy->x_pos))
		enemy->y_pos = move_y;
}