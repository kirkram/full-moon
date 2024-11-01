/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_frame2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:48:45 by mburakow          #+#    #+#             */
/*   Updated: 2024/10/23 11:40:58 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_idle_frame(t_enemy *enemy, int index, double now, double prev)
{
	if (now - prev > 0.7)
	{
		if (enemy->current_frame == index + 96)
			enemy->current_frame = index + 88;
		else
			enemy->current_frame = index + 96;
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
			enemy->current_frame = index + 24;
		else
			enemy->current_frame = index;
		enemy->last_frame = now;
	}
}

void	update_attacking_frame(t_enemy *enemy, int index, double now, double prev)
{
	if (now - prev > 0.4)
	{
		if (enemy->current_frame == index + 32)
			enemy->current_frame = index + 40;
		else if (enemy->current_frame == index + 40)
			enemy->current_frame = index + 48;
		else if (enemy->current_frame == index + 48)
			enemy->current_frame = index + 56;
		else if (enemy->current_frame == index + 56)
			enemy->current_frame = index + 64;
		else if (enemy->current_frame == index + 64)
		{
			enemy->current_frame = index + 72;
			enemy->attacked = false;
		}
		else
			enemy->current_frame = index + 32;
		enemy->last_frame = now;
	}
}

void	update_taking_damage_frame(t_enemy *enemy, int index, double now, double prev)
{
	//printf("Updating takedamage frame: %f\n", (now - prev));
	enemy->current_frame = index + 80;
	if (now - prev > 0.7)
	{
		if (enemy->current_frame == index + 80)
		{
			//enemy->current_frame = index + 88;
			enemy->state = IDLE;
			// printf("Enemy state is now IDLE\n");
		}
		enemy->last_frame = now;
	}
}

void	update_dying_frame(t_enemy *enemy, double now, double prev)
{
	if (now - prev > 0.3)
	{
		if (enemy->deathanim == 0)
		{
			if (enemy->current_frame >= 104 && enemy->current_frame < 110)
			{
				enemy->current_frame++;
				if (enemy->current_frame == 110)
					enemy->state = DEAD;
			}
			else
				enemy->current_frame = 104;
		}
		else
		{
			if (enemy->current_frame >= 112 && enemy->current_frame < 117)
			{
				enemy->current_frame++;
				if (enemy->current_frame == 117)
					enemy->state = DEAD;
			}
			else
				enemy->current_frame = 112;
		}
		enemy->last_frame = now;
	}
}
