/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maploader3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:23:27 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 11:00:26 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Some of the code is just for fun like enemy facing determined 
// by order of appearance
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
	enemy->seen_player = false;
	enemy->route = NULL;
	enemy->speed = 3.0;
	enemy->x_target = enemy->x_pos;
	enemy->y_target = enemy->y_pos;
	enemy->attacked = false;
	update_enemy_frame(enemy, data);
}

static int	expand_enemies_array(t_enemy ***enemies, int y, char *line,
	t_data *data)
{
	int	i;

	i = 0;
	if (data->enemies != NULL)
	{
		while (data->enemies[i] != NULL)
			i++;
	}
	*enemies = ft_calloc((i + 2), sizeof(t_enemy *));
	if (!*enemies)
		map_validation_error("Error\nEnemies malloc fail.\n", y, line, data);
	i = 0;
	if (data->enemies != NULL)
	{
		while (data->enemies[i])
		{
			*enemies[i] = data->enemies[i];
			i++;
		}
	}
	return (i);
}

void	add_new_enemy(int x, int y, t_data *data, char *line)
{
	t_enemy		*enemy;
	t_enemy		**enemies;
	size_t		i;

	enemies = NULL;
	data->world_map[y][x] = 0;
	enemy = (t_enemy *)malloc(sizeof(t_enemy));
	if (!enemy)
		map_validation_error("Error\nEnemy malloc fail.\n", y, line, data);
	enemy->x_pos = (float)x + 0.5;
	enemy->y_pos = (float)y + 0.5;
	i = expand_enemies_array(&enemies, y, line, data);
	enemies[i] = enemy;
	enemies[i + 1] = NULL;
	if (data->enemies != NULL)
		free(data->enemies);
	data->enemies = enemies;
	init_enemy_state(data->enemies[i], data);
}
