/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:46:24 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/12 13:49:11 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_d(t_data *data, t_map *map)
{
	t_player	*player;

	player = data->player;
	calc_collision_ad(data, map, false);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1
			&& data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += data->speed * cosf(player->angle + PI_S);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1
			&& data->world_map[map->y][(int)data->player->x_pos] != 4)
		{
			player->y_pos += data->speed * sinf(player->angle + PI_S);
			data->player->y_pos_mini = data->player->y_pos * data->zoom;
		}
	}
}

static void	movement_a(t_data *data, t_map *map)
{
	t_player	*player;

	player = data->player;
	calc_collision_ad(data, map, true);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1
			&& data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += -data->speed * cosf(player->angle + PI_S);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1
			&& data->world_map[map->y][(int)data->player->x_pos] != 4)
		{
			player->y_pos += -data->speed * sinf(player->angle + PI_S);
			data->player->y_pos_mini = data->player->y_pos * data->zoom;
		}
	}
}

static void	movement_s(t_data *data, t_map *map)
{
	t_player	*player;

	player = data->player;
	calc_collision_ws(data, map, false);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1
			&& data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += -data->speed * cosf(player->angle);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1
			&& data->world_map[map->y][(int)data->player->x_pos] != 4)
		{
			player->y_pos += -data->speed * sinf(player->angle);
			data->player->y_pos_mini = data->player->y_pos * data->zoom;
		}
	}
}

static void	movement_w(t_data *data, t_map *map)
{
	t_player	*player;

	player = data->player;
	calc_collision_ws(data, map, true);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1
			&& data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += data->speed * cosf(player->angle);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1
			&& data->world_map[map->y][(int)data->player->x_pos] != 4)
		{
			player->y_pos += data->speed * sinf(player->angle);
			data->player->y_pos_mini = data->player->y_pos * data->zoom;
		}
	}
}

void	movement_loop(t_data *data, t_map *map)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->angle -= (data->speed / 1.5);
		if (data->player->angle < 0)
			data->player->angle = PI2 - (-data->player->angle);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->angle += (data->speed / 1.5);
		if (data->player->angle > PI2)
			data->player->angle = data->player->angle - PI2;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		movement_w(data, map);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		movement_s(data, map);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		movement_a(data, map);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		movement_d(data, map);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		open_door(data, map);
}
