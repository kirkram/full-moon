/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/28 14:49:46 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_hook_movement(t_data *data)
{
	t_player	*player;
	t_map		map;
	float		x_off;
	float		y_off;
	double		current_time;

	player = data->player;
	data->speed = 0.003 / (1 / data->mlx->delta_time / 1000);
	//printf("The fps is %f\n", 1 / data->mlx->delta_time);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		player->angle -= (data->speed / 1.5);
		if (player->angle < 0)
			player->angle = PI2 - (-player->angle);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		player->angle += (data->speed / 1.5);
		if (player->angle > PI2)
			player->angle = player->angle - PI2;
	}
	y_off = COLL;
	x_off = COLL;
	if (player->angle > PI_S && player->angle < PI_N)
		x_off = -COLL;
	if (player->angle > PI)
		y_off = -COLL;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		map.y = floorf(data->player->y_pos + y_off);
		map.x = floorf(data->player->x_pos + x_off);
		if ((map.y >= 0 && map.y < data->map_height && map.x >= 0 && map.x < data->map_width))
		{
			if (data->world_map[(int)data->player->y_pos][map.x] != 1)
			{
				player->x_pos += data->speed * cosf(player->angle);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += data->speed * sinf(player->angle);
				data->player->y_pos_mini = data->player->y_pos * data->zoom;
			}
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		map.y = floorf(data->player->y_pos - y_off);
		map.x = floorf(data->player->x_pos - x_off);
		if ((map.y >= 0 && map.y < data->map_height && map.x >= 0 && map.x < data->map_width))
		{
			if (data->world_map[(int)data->player->y_pos][map.x] != 1)
			{
				player->x_pos += -data->speed * cosf(player->angle);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += -data->speed * sinf(player->angle);
				data->player->y_pos_mini = data->player->y_pos * data->zoom;
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (player->angle > PI_S && player->angle < PI_N)
			y_off = COLL;
		else 
			y_off = -COLL;		
		if (player->angle > PI)
			x_off = -COLL;
		else 
			x_off = COLL;
		map.y = floorf(data->player->y_pos + y_off);
		map.x = floorf(data->player->x_pos + x_off);
		// printf("ang is %f, player->y is %f, map.y is %d\n", player->angle, player->y_pos, map.y);
		if ((map.y >= 0 && map.y < data->map_height && map.x >= 0 && map.x < data->map_width))
		{
			if (data->world_map[(int)data->player->y_pos][map.x] != 1)
			{
				player->x_pos += -data->speed * cosf(player->angle + PI_S);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += -data->speed * sinf(player->angle + PI_S);
				data->player->y_pos_mini = data->player->y_pos * data->zoom;
			}
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (player->angle > PI_S && player->angle < PI_N)
			y_off = -COLL;
		else 
			y_off = COLL;
		if (player->angle > PI)
			x_off = COLL;
		else 
			x_off = -COLL;
		map.y = floorf(data->player->y_pos + y_off);
		map.x = floorf(data->player->x_pos + x_off);
		if ((map.y >= 0 && map.y < data->map_height && map.x >= 0 && map.x < data->map_width))
		{
			if (data->world_map[(int)data->player->y_pos][map.x] != 1)
			{
				player->x_pos += data->speed * cosf(player->angle + PI_S);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += data->speed * sinf(player->angle + PI_S);
				data->player->y_pos_mini = data->player->y_pos * data->zoom;
			}
		}
	}
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
	if ((current_time - last_update >= ANIMATION_SPEED / 4) &&
			(current_time - data->last_attack >= ANIMATION_SPEED))
	{
		mlx_delete_image(data->mlx, data->swordarm);
		data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[frame]);
		frame++;
		if (frame > 3)
			frame = 0;
		mlx_image_to_window(data->mlx, data->swordarm, 240, 1);
		last_update = mlx_get_time();
	}
	else if (current_time - data->last_attack < ANIMATION_SPEED)
	{
		mlx_delete_image(data->mlx, data->swordarm);
		if (current_time - data->last_attack < (ANIMATION_SPEED) / 10)
			data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[7]);
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 8))
			data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[8]);
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 6))
			data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[9]);
		else
			data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[10]);
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
	t_data		*data;

	data = param;
	ft_hook_movement(data);
	color_whole_image(data->screen, FULL_TRANSPARENT,
		data->width, data->height);
	hook_animation(data);
	color_whole_image(data->player->img, FULL_TRANSPARENT,
		data->player->imgwidth, data->player->imgheight);
	draw_player(data);
	draw_rays(data, data->ray);
}

void	hook_mouse_move(double x, double y, void* param) 
{
	t_data		*data;
	t_player	*player;

	(void)y;
	data = param;
	player = data->player;
    double dx = x - data->width / 2;
    player->angle += dx * DEGR * 1.5 * data->speed;
    if (player->angle < 0) player->angle += PI2;
    if (player->angle >= PI2) player->angle -= PI2;
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}
