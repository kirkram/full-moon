/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_movement_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:50:04 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/07 18:41:52 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_data *data)
{
	float	x_off;
	float	y_off;


	y_off = COLL * 4;
	x_off = COLL * 4;
	if (data->player->angle > PI_S && data->player->angle < PI_N)
		x_off = -COLL * 4;
	if (data->player->angle > PI)
		y_off = -COLL * 4;
	data->keyhook_map.y = floorf(data->player->y_pos + y_off);
	data->keyhook_map.x = floorf(data->player->x_pos + x_off);
	if ((data->keyhook_map.y >= 0 && data->keyhook_map.y < data->map_height && \
	 data->keyhook_map.x >= 0 && data->keyhook_map.x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][data->keyhook_map.x] == 4)
			data->world_map[(int)data->player->y_pos][data->keyhook_map.x] = 6;
		else if (data->world_map[(int)data->player->y_pos][data->keyhook_map.x] == 6)
			data->world_map[(int)data->player->y_pos][data->keyhook_map.x] = 4;
		if (data->world_map[data->keyhook_map.y][(int)data->player->x_pos] == 4)
			data->world_map[data->keyhook_map.y][(int)data->player->x_pos] = 6;
		if (data->world_map[data->keyhook_map.y][(int)data->player->x_pos] == 6)
			data->world_map[data->keyhook_map.y][(int)data->player->x_pos] = 4;
	}
}

void	calc_collision_ad(t_data *data, t_map *map, bool left)
{
	float	x_off;
	float	y_off;

	if (data->player->angle > PI_S && data->player->angle < PI_N)
		y_off = COLL;
	else
		y_off = -COLL;
	if (data->player->angle > PI)
		x_off = -COLL;
	else
		x_off = COLL;
	if (left == true)
	{
		map->y = floorf(data->player->y_pos + y_off);
		map->x = floorf(data->player->x_pos + x_off);
	}
	else
	{
		map->y = floorf(data->player->y_pos - y_off);
		map->x = floorf(data->player->x_pos - x_off);
	}
}

void	calc_collision_ws(t_data *data, t_map *map, bool forward)
{
	float	x_off;
	float	y_off;

	if (data->player->angle > PI_S && data->player->angle < PI_N)
		x_off = -COLL;
	else
		x_off = COLL;
	if (data->player->angle > PI)
		y_off = -COLL;
	else
		y_off = COLL;
	if (forward == true)
	{
		map->y = floorf(data->player->y_pos + y_off);
		map->x = floorf(data->player->x_pos + x_off);
	}
	else
	{
		map->y = floorf(data->player->y_pos - y_off);
		map->x = floorf(data->player->x_pos - x_off);
	}
}
