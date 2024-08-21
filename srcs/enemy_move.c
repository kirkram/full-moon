/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:47:24 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 14:40:57 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	calculate_distance(t_fcoord direction)
{
	return (sqrtf(direction.x * direction.x + direction.y * direction.y));
}

static void	normalize_direction(t_fcoord *direction, float distance)
{
	direction->x /= distance;
	direction->y /= distance;
}

static t_fcoord	calculate_direction(t_enemy *enemy)
{
	t_fcoord	direction;

	direction.x = enemy->x_target - enemy->x_pos;
	direction.y = enemy->y_target - enemy->y_pos;
	return (direction);
}

static float	calculate_delta_time(t_data *data)
{
	float	delta_time;

	delta_time = data->mlx->delta_time;
	if (delta_time > MAX_DELTA)
	{
		delta_time = MAX_DELTA;
	}
	return (delta_time);
}

void	move_enemy(t_data *data, t_enemy *enemy)
{
	float		delta_time;
	t_fcoord	direction;
	float		distance;

	delta_time = calculate_delta_time(data);
	direction = calculate_direction(enemy);
	distance = calculate_distance(direction);
	if (distance > 0)
	{
		normalize_direction(&direction, distance);
		move_enemy_position(data, enemy, direction, delta_time);
	}
}

/*
// Initial version
static void	move_enemy(t_data *data, t_enemy *enemy)
{
	float	move_x;
	float	move_y;
	float	direction_x;
	float	direction_y;
	float	distance;
	float	delta_time;

	delta_time = data->mlx->delta_time;
	if (delta_time > MAX_DELTA)
		delta_time = MAX_DELTA;
	direction_x = enemy->x_target - enemy->x_pos;
	direction_y = enemy->y_target - enemy->y_pos;
	distance = sqrtf(direction_x * direction_x + direction_y * direction_y);
	// printf("distance: %f\n", distance);
	if (distance > 0)
	{
		direction_x /= distance;
		direction_y /= distance;
		move_x = direction_x * ENEMYSPEED * delta_time + enemy->x_pos;
		move_y = direction_y * ENEMYSPEED * delta_time + enemy->y_pos;
		if ((direction_x > 0 && move_x > enemy->x_target) || (direction_x < 0
				&& move_x < enemy->x_target))
			move_x = enemy->x_target;
		if ((direction_y > 0 && move_y > enemy->y_target) || (direction_y < 0
				&& move_y < enemy->y_target))
			move_y = enemy->y_target;
		// printf("Moving from x %f y %f to x %f y %f\n", enemy->x_pos,
		//	enemy->y_pos, move_x, move_y);
		if (move_x >= 0 && move_x < data->map_width && move_y >= 0
			&& move_y < data->map_height)
		{
			if (data->world_map[(int)enemy->y_pos][(int)move_x] != 1
				&& data->world_map[(int)enemy->y_pos][(int)move_x] != 4)
				enemy->x_pos = move_x;
			if (data->world_map[(int)move_y][(int)enemy->x_pos] != 1
				&& data->world_map[(int)move_y][(int)enemy->x_pos] != 4)
				enemy->y_pos = move_y;
		}
	}
}
*/