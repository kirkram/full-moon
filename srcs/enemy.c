/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 11:42:56 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	update_enemy_frame(t_enemy *enemy, t_data *data)
{
	float	a;
	float	b;
	double	prev;
	double	now;
	int		index;

	if (enemy->state == DEAD)
	{
		enemy->current_frame = 61;
		return ;
	}
	a = normalize_degr(enemy->angle / DEGR);
	b = normalize_degr(data->player->angle / DEGR);
	a = normalize_degr(b - a);
	index = (int)((a + 22.5) / 45) % 8;
	index = (8 - index) % 8;
	now = mlx_get_time();
	if (enemy->last_frame == 0.0)
	{
		enemy->current_frame = index;
		enemy->last_frame = now;
		return ;
	}
	prev = enemy->last_frame;
	if (enemy->state == IDLE && (now - prev > 0.7))
	{
		if (enemy->current_frame == index)
			enemy->current_frame = index + 48;
		else
			enemy->current_frame = index;
		enemy->last_frame = now;
		return ;
	}
	else if (enemy->state == WALKING && now - prev > 0.2)
	{
		if (enemy->current_frame == index)
			enemy->current_frame = index + 8;
		else if (enemy->current_frame == index + 8)
			enemy->current_frame = index + 16;
		else if (enemy->current_frame == index + 16)
			enemy->current_frame = index + 32;
		else
			enemy->current_frame = index;
		enemy->last_frame = now;
		return ;
	}
	else if (enemy->state == DYING && now - prev > 0.3)
	{
		if (enemy->current_frame >= 56 && enemy->current_frame < 61)
		{
			enemy->current_frame++;
			if (enemy->current_frame == 61)
				enemy->state = DEAD;
		}
		else
			enemy->current_frame = 56;
		enemy->last_frame = now;
		return ;
	}
}

bool	enemy_is_alive(t_enemy *enemy)
{
	if (enemy->state == DEAD || enemy->state == DYING)
		return (false);
	else
		return (true);
}

static void	step_route(t_enemy *enemy)
{
	int	i;

	i = 0;
	while (enemy->route->coords[i].x != -1)
	{
		enemy->route->coords[i].x = enemy->route->coords[i + 1].x;
		enemy->route->coords[i].y = enemy->route->coords[i + 1].y;
		i++;
	}
}

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

void	draw_enemy(t_data *data, t_enemy *enemy, uint32_t screen_x)
{
	uint32_t	screen_y;

	if (enemy->distance < 1.0)
		enemy->distance = 1.0;
	enemy->scale = ESCALE / enemy->distance;
	screen_x = screen_x - (ESW * enemy->scale) / 2;
	screen_y = data->mlx->height / 2 - (ESH * enemy->scale) / 2.6;
	draw_enemy_onto_canvas(enemy, screen_x, screen_y, data);
}

void	hook_enemies(t_data *data)
{
	int i;
	uint32_t screen_x;

	i = -1;
	while (data->enemies[++i] != NULL)
		get_rel_angle_and_pos(data->enemies[i], data);
	sort_enemy_arr(data);
	i = -1;
	while (data->enemies[++i] != NULL)
	{
		update_enemy(data->enemies[i], data);
		update_enemy_frame(data->enemies[i], data);
		if (data->enemies[i]->visible)
		{
			screen_x = (uint32_t)((data->enemies[i]->rel_angle + rad(FOV / 2))
					/ rad(FOV) * data->width);
			draw_enemy(data, data->enemies[i], screen_x);
		}
	}
	i = -1;
	while (data->enemies[++i] != NULL)
	{
		find_enemy_rays(data, data->enemies[i]);
	}
}