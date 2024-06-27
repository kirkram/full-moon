/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/27 17:38:31 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_hook_movement(t_data *data)
{
	t_player	*player;
	float		speed;

	player = data->player;
	speed = 0.003 / (1 / data->mlx->delta_time / 1000);
	// test with giant framerate
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		player->x_pos += speed * cos(player->angle);
		player->y_pos += speed * sin(player->angle);
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		player->x_pos += -speed * cos(player->angle);
		player->y_pos += -speed * sin(player->angle);
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		player->x_pos += -speed * cos(player->angle + rad(90));
		player->y_pos += -speed * sin(player->angle + rad(90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		player->x_pos += speed * cos(player->angle + rad(90));
		player->y_pos += speed * sin(player->angle + rad(90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		player->angle -= (speed / 1.5);
		if (player->angle < 0)
			player->angle = PI * 2 - (-player->angle);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		player->angle += (speed / 1.5);
		if (player->angle > PI * 2)
			player->angle = player->angle - PI * 2;
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
	//t_player	prev;

	data = param;
	//prev = *(data->player);
	ft_hook_movement(data);
	hook_animation(data);
	/*
	if (prev.x_pos_mini != data->player->x_pos_mini
		|| prev.y_pos_mini != data->player->y_pos_mini
		|| prev.angle != data->player->angle)
	{
	*/
	color_whole_image(data->screen, FULL_TRANSPARENT,
		data->player->imgwidth, data->player->imgheight);
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
