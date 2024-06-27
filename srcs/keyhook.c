/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/27 17:42:55 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_hook_movement(t_data *data)
{
	t_player	*player;
	t_map		map;
	float		speed;
	float		x_off;
	float		y_off;

	player = data->player;
	speed = 0.003 / (1 / data->mlx->delta_time / 1000);
	//printf("The fps is %f\n", 1 / data->mlx->delta_time);

	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		player->angle -= (speed / 1.5);
		if (player->angle < 0)
			player->angle = PI2 - (-player->angle);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		player->angle += (speed / 1.5);
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
				player->x_pos += speed * cosf(player->angle);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += speed * sinf(player->angle);
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
				player->x_pos += -speed * cosf(player->angle);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += -speed * sinf(player->angle);
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
		printf("ang is %f, player->y is %f, map.y is %d\n", player->angle, player->y_pos, map.y);
		if ((map.y >= 0 && map.y < data->map_height && map.x >= 0 && map.x < data->map_width))
		{
			if (data->world_map[(int)data->player->y_pos][map.x] != 1)
			{
				player->x_pos += -speed * cosf(player->angle + PI_S);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += -speed * sinf(player->angle + PI_S);
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
				player->x_pos += speed * cosf(player->angle + PI_S);
				data->player->x_pos_mini = data->player->x_pos * data->zoom;
			}
			if (data->world_map[map.y][(int)data->player->x_pos] != 1)
			{
				player->y_pos += speed * sinf(player->angle + PI_S);
				data->player->y_pos_mini = data->player->y_pos * data->zoom;
			}
		}
	}
}

void	hook_animation(t_data *data)
{
	static double	last_update = 0;
	static int		frame = 0;
	double			current_time;
	
	current_time = mlx_get_time();
	printf("current time: %f\n", current_time);
	if (current_time - last_update >= ANIMATION_SPEED / 10)
	{
		mlx_delete_image(data->mlx, data->swordarm);
		data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[frame]);
		frame++;
		if (frame > 10)
			frame = 0;
		mlx_image_to_window(data->mlx, data->swordarm, 240, 1);
		last_update = mlx_get_time();
		printf("last update: %f\n", last_update);
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

void hook_mouse_move(double x, double y, void* param) 
{
	t_data			*data;
	t_player		*player;

	data = param;
	player = data->player;
    double dx = x - data->width / 2;
	// bs code to silence complire complaint for y
    y = y + 1;

	if (y > 2)
		y = 0;
    player->angle += dx * DEGR / 10;
    if (player->angle < 0) player->angle += PI2;
    if (player->angle >= PI2) player->angle -= PI2;
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
    //printf("Player angle: %f\n", player->angle);
}
