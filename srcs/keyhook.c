/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/12 13:47:30 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_hook_keys(t_data *data)
{
	t_map	map;
	double	current_time;

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
		last_update = mlx_get_time();
	}
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
	color_whole_image(data->enemy_img, FULL_TRANSPARENT, data->player->imgwidth,
		data->player->imgheight);
	hook_enemies(data);
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
