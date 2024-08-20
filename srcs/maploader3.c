/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:23:27 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 19:24:10 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Some of the code is just for fun like enemy facing determined by order of appearance
static void	init_enemy_state(t_enemy *enemy, t_data *data)
{
	static int	facing = -1;

	facing++;
	if (facing > 7)
		facing = 0;
	enemy->distance = 0.0;
	enemy->angle = rad(facing * 45);
	enemy->rel_angle = 0.0;
	enemy->last_frame = 0.0;
	enemy->state = IDLE;
	enemy->visible = 0;
	enemy->scale = 1.0;
	enemy->attack = false;
	enemy->route = NULL;
	enemy->speed = 3.0;
	enemy->x_target = enemy->x_pos;
	enemy->y_target = enemy->y_pos;
	update_enemy_frame(enemy, data);
}

void	add_new_enemy(int x, int y, t_data *data, char *line)
{
	t_enemy		*enemy;
	t_enemy		**enemies;
	size_t		i;

	data->world_map[y][x] = 0;
	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		map_validation_error("Error: enemy malloc fail.\n", y, line, data);
	enemy->x_pos = (float)x + 0.5;
	enemy->y_pos = (float)y + 0.5;
	i = 0;
	if (data->enemies != NULL)
	{
		while (data->enemies[i] != NULL)
			i++;
	}
	enemies = ft_calloc((i + 2), sizeof(t_enemy *));
	if (!enemies)
		map_validation_error("Error: enemies malloc fail.\n", y, line, data);
	i = 0;
	if (data->enemies != NULL)
	{
		while (data->enemies[i])
		{
			enemies[i] = data->enemies[i];
			i++;
		}
	}
	enemies[i] = enemy;
	enemies[i + 1] = NULL;
	if (data->enemies != NULL)
		free(data->enemies);
	data->enemies = enemies;
	init_enemy_state(data->enemies[i], data);
	// printf("enemy found at %.0f, %.0f : angle: %.4f\n", enemy->x_pos, enemy->y_pos, degr(enemy->angle));
}