/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_frame2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:48:45 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/26 11:37:25 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_idle_frame(t_enemy *enemy, int index, double now, double prev)
{
	if (now - prev > 0.7)
	{
		if (enemy->current_frame == index)
			enemy->current_frame = index + 48;
		else
			enemy->current_frame = index;
		enemy->last_frame = now;
	}
}

void	update_walking_frame(t_enemy *enemy, int index, double now, double prev)
{
	if (now - prev > 0.2)
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
	}
}

void	update_attacking_frame(t_enemy *enemy, double now, double prev)
{
	if (now - prev > 0.3)
	{
		if (enemy->current_frame == 32)
			enemy->current_frame = 40;
		else if (enemy->current_frame == 40)
		{
			enemy->current_frame = 48;
			enemy->attacked = false;
		}
		else
			enemy->current_frame = 32;
		enemy->last_frame = now;
	}
}

void	update_dying_frame(t_enemy *enemy, double now, double prev)
{
	if (now - prev > 0.3)
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
	}
}
