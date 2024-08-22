/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:52:40 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/22 19:11:49 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_animation_frame(t_data *data, double *last_update,
		int *frame, double current_time)
{
	if (current_time - *last_update >= ATTACK_SPEED / 4)
	{
		mlx_delete_image(data->mlx, data->swordarm);
		data->swordarm = mlx_texture_to_image(data->mlx,
				data->swordarm_tx[*frame]);
		(*frame)++;
		if (*frame > 3)
			*frame = 0;
		mlx_image_to_window(data->mlx, data->swordarm, data->width * 0.45, 1);
		*last_update = current_time;
	}
}

static void	handle_attack_animation(t_data *data, double current_time)
{
	mlx_delete_image(data->mlx, data->swordarm);
	if (current_time - data->last_attack < ATTACK_SPEED / 10)
		data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[7]);
	else if (current_time - data->last_attack < ATTACK_SPEED / 8)
		data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[8]);
	else if (current_time - data->last_attack < ATTACK_SPEED / 6)
	{
		data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[9]);
		hit_enemy_if_in_range(data);
	}
	else
		data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[10]);
	mlx_image_to_window(data->mlx, data->swordarm, 240, 1);
}

static void	check_and_handle_attack(t_data *data, double current_time)
{
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (current_time - data->last_attack >= ATTACK_SPEED)
			data->last_attack = current_time;
	}
}

static void	handle_sword_animation(t_data *data, double *last_update,
		int *frame, double current_time)
{
	if (current_time - data->last_attack >= ATTACK_SPEED)
	{
		update_animation_frame(data, last_update, frame, current_time);
	}
	else if (current_time - data->last_attack < ATTACK_SPEED)
	{
		handle_attack_animation(data, current_time);
	}
}

void	hook_player_animation(t_data *data)
{
	static double	last_update = -1;
	static int		frame = 0;
	double			current_time;

	current_time = mlx_get_time();
	if (last_update < 0)
		last_update = current_time;
	handle_sword_animation(data, &last_update, &frame, current_time);
	check_and_handle_attack(data, current_time);
}

/*
void	hook_player_animation(t_data *data)
{
	static double	last_update = -1;
	static int		frame = 0;
	double			current_time;

	current_time = mlx_get_time();
	if (last_update < 0)
		last_update = current_time;
	if ((current_time - last_update >= ATTACK_SPEED / 4) && (current_time
			- data->last_attack >= ATTACK_SPEED))
	{
		mlx_delete_image(data->mlx, data->swordarm);
		data->swordarm = mlx_texture_to_image(data->mlx,
				data->swordarm_tx[frame]);
		frame++;
		if (frame > 3)
			frame = 0;
		mlx_image_to_window(data->mlx, data->swordarm, data->width * 0.45, 1);
		last_update = current_time;
	}
	else if (current_time - data->last_attack < ATTACK_SPEED)
	{
		mlx_delete_image(data->mlx, data->swordarm);
		if (current_time - data->last_attack < (ATTACK_SPEED) / 10)
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[7]);
		else if (current_time - data->last_attack < (ATTACK_SPEED / 8))
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[8]);
		else if (current_time - data->last_attack < (ATTACK_SPEED / 6))
		{
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[9]);
			hit_enemy_if_in_range(data);
		}
		else
			data->swordarm = mlx_texture_to_image(data->mlx,
					data->swordarm_tx[10]);
		mlx_image_to_window(data->mlx, data->swordarm, 240, 1);
	}
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (current_time - data->last_attack >= ATTACK_SPEED)
			data->last_attack = current_time;
	}
}
*/