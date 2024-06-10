/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/10 18:19:37 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_hook_movement(t_data *data)
{
	t_player	*player;

	player = data->player;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		player->x_pos += SPEED * cos(player->angle);
		player->y_pos += SPEED * sin(player->angle);
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		player->x_pos += -SPEED * cos(player->angle);
		player->y_pos += -SPEED * sin(player->angle);
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		player->x_pos += -SPEED * cos(player->angle + rad(90));
		player->y_pos += -SPEED * sin(player->angle + rad(90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		player->x_pos += SPEED * cos(player->angle + rad(90));
		player->y_pos += SPEED * sin(player->angle + rad(90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		player->angle -= (SPEED / 1.5);
		if (player->angle < 0)
			player->angle = PI * 2 - (-player->angle);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		player->angle += (SPEED / 1.5);
		if (player->angle > PI * 2)
			player->angle = player->angle - PI * 2;
	}
}

void	ft_hook_hub(void *param)
{
	t_data		*data;
	t_player	prev;

	data = param;
	prev = *(data->player);
	ft_hook_movement(data);
	if (prev.x_pos_mini != data->player->x_pos_mini || \
	prev.y_pos_mini != data->player->y_pos_mini || \
	prev.angle != data->player->angle)
	{
		color_whole_image(data->screen, FULL_TRANSPARENT, data->player->imgwidth, data->player->imgheight);
		draw_screen(data);
		color_whole_image(data->player->img, FULL_TRANSPARENT, data->player->imgwidth, data->player->imgheight);
		draw_player(data);
		calc_rays(data, data->ray);
	}
}
