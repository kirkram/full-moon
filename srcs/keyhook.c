/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/11 16:23:22 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void open_door(t_data *data, t_map *map)
{
	float	x_off;
	float	y_off;
	
	y_off = COLL * 4;
	x_off = COLL * 4;
	if (data->player->angle > PI_S && data->player->angle < PI_N)
		x_off = -COLL * 4;
	if (data->player->angle > PI)
		y_off = -COLL * 4;
	map->y = floorf(data->player->y_pos + y_off);
	map->x = floorf(data->player->x_pos + x_off);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] == 4)
			data->world_map[(int)data->player->y_pos][map->x] = 0;
		if (data->world_map[map->y][(int)data->player->x_pos] == 4)
			data->world_map[map->y][(int)data->player->x_pos] = 0;
	}
}


static void calc_collision_ad(t_data *data, t_map *map, bool left)
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

static void calc_collision_ws(t_data *data, t_map *map, bool forward)
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

static void movement_d(t_data *data, t_map *map)
{
	t_player *player;

	player = data->player;
	calc_collision_ad(data, map, false);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1 && \
		data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += data->speed * cosf(player->angle + PI_S);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1 && \
		data->world_map[map->y][(int)data->player->x_pos] != 4)
		{
			player->y_pos += data->speed * sinf(player->angle + PI_S);
			data->player->y_pos_mini = data->player->y_pos * data->zoom;
		}
	}
}

static void movement_a(t_data *data, t_map *map)
{
	t_player *player;

	player = data->player;
	calc_collision_ad(data, map, true);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1 && \
		data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += -data->speed * cosf(player->angle + PI_S);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1 && \
		data->world_map[map->y][(int)data->player->x_pos] != 4)
		{
			player->y_pos += -data->speed * sinf(player->angle + PI_S);
			data->player->y_pos_mini = data->player->y_pos * data->zoom;
		}
	}
}

static void movement_s(t_data *data, t_map *map)
{
	t_player *player;

	player = data->player;
	calc_collision_ws(data, map, false);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1 && \
		data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += -data->speed * cosf(player->angle);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1 && \
		data->world_map[map->y][(int)data->player->x_pos] != 4)
		{
			player->y_pos += -data->speed * sinf(player->angle);
			data->player->y_pos_mini = data->player->y_pos * data->zoom;
		}
	}
}

static void movement_w(t_data *data, t_map *map)
{
	t_player *player;

	player = data->player;
	calc_collision_ws(data, map, true);
	if ((map->y >= 0 && map->y < data->map_height && map->x >= 0
			&& map->x < data->map_width))
	{
		if (data->world_map[(int)data->player->y_pos][map->x] != 1 && \
		data->world_map[(int)data->player->y_pos][map->x] != 4)
		{
			player->x_pos += data->speed * cosf(player->angle);
			data->player->x_pos_mini = data->player->x_pos * data->zoom;
		}
		if (data->world_map[map->y][(int)data->player->x_pos] != 1 && \
		data->world_map[map->y][(int)data->player->x_pos] != 4)
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

static void	ft_hook_keys(t_data *data)
{
	t_map		map;
	double		current_time;

	data->speed = 0.003 / (1 / data->mlx->delta_time / 1000);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		free_all_and_quit(data, "Bye!", 0);
	movement_loop(data, &map);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
	{
		current_time = mlx_get_time();
		if (current_time - data->last_attack >= ANIMATION_SPEED)
			attack_animation(data);
	}
}

// here logic for attack
void	attack_animation(t_data *data)
{
	data->last_attack = mlx_get_time();
}

void	hook_animation(t_data *data)
{
	static double	last_update = 0;
	static int		frame = 0;
	double			current_time;

	current_time = mlx_get_time();
	if ((current_time - last_update >= ANIMATION_SPEED / 4) && (current_time
			- data->last_attack >= ANIMATION_SPEED))
	{
		mlx_delete_image(data->mlx, data->swordarm);
		data->swordarm = mlx_texture_to_image(data->mlx,
				data->swordarm_tx[frame]);
		frame++;
		if (frame > 3)
			frame = 0;
		mlx_image_to_window(data->mlx, data->swordarm, data->width * 0.45, 1);
		//mlx_set_instance_depth(data->swordarm, 100);
		last_update = mlx_get_time();
	}
	// Fix to use image array instead
	else if (current_time - data->last_attack < ANIMATION_SPEED)
	{
		mlx_delete_image(data->mlx, data->swordarm);
		if (current_time - data->last_attack < (ANIMATION_SPEED) / 10)
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[7]);
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 8))
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[8]);
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 6))
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[9]);
		else
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[10]);
		mlx_image_to_window(data->mlx, data->swordarm, 240, 1);
	}
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (current_time - data->last_attack >= ANIMATION_SPEED)
			attack_animation(data);
	}
}

void	ft_hook_hub(void *param)
{
	t_data	*data;

	data = param;
	ft_hook_keys(data);
	color_whole_image(data->screen, FULL_TRANSPARENT, data->width,
		data->height);
	hook_animation(data);
	color_whole_image(data->player->img, FULL_TRANSPARENT,
		data->player->imgwidth, data->player->imgheight);
	draw_player_minimap(data);
	draw_rays(data);
	color_whole_image(data->enemy_img, FULL_TRANSPARENT,
		data->player->imgwidth, data->player->imgheight);
	hook_enemies(data);
	mlx_image_to_window(data->mlx, data->enemy_img, 0, 0);
}

void	hook_mouse_move(double x, double y, void *param)
{
	t_data		*data;
	t_player	*player;
	double		dx;

	(void)y;
	data = param;
	player = data->player;
	dx = x - data->width / 2;
	player->angle += dx * DEGR * 1.5 * data->speed * 0.2;
	if (player->angle < 0)
		player->angle += PI2;
	if (player->angle >= PI2)
		player->angle -= PI2;
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}
