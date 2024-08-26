/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:35:17 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/26 11:20:23 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_frame_based_on_state(t_enemy *enemy, int index, double now)
{
	double	prev;

	prev = enemy->last_frame;
	if (enemy->state == IDLE)
		update_idle_frame(enemy, index, now, prev);
	else if (enemy->state == WALKING)
		update_walking_frame(enemy, index, now, prev);
	else if (enemy->state == ATTACKING)
		update_attacking_frame(enemy, now, prev);
	else if (enemy->state == DYING)
		update_dying_frame(enemy, now, prev);
}

static int	calculate_direction_index(t_enemy *enemy, t_data *data)
{
	float	a;
	float	b;
	int		index;

	a = normalize_degr(enemy->angle / DEGR);
	b = normalize_degr(data->player->angle / DEGR);
	a = normalize_degr(b - a);
	index = (int)((a + 22.5) / 45) % 8;
	return ((8 - index) % 8);
}

void	update_enemy_frame(t_enemy *enemy, t_data *data)
{
	int		index;
	double	now;

	if (enemy->state == DEAD)
	{
		enemy->current_frame = 61;
		return ;
	}
	index = calculate_direction_index(enemy, data);
	now = mlx_get_time();
	if (enemy->last_frame == 0.0)
	{
		enemy->current_frame = index;
		enemy->last_frame = now;
		return ;
	}
	update_frame_based_on_state(enemy, index, now);
}
