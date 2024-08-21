/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 15:14:02 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	enemy_is_alive(t_enemy *enemy)
{
	if (enemy->state == DEAD || enemy->state == DYING)
		return (false);
	else
		return (true);
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
	int			i;
	uint32_t	screen_x;

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