/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/09/15 21:09:41 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook_keys(t_data *data)
{
	double	current_time;

	if (data->player->is_dead)
		return ;
	data->speed = 0.003 / (1 / data->mlx->delta_time / 1000);
	movement_loop(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
	{
		current_time = mlx_get_time();
		if (current_time - data->last_attack >= ATTACK_SPEED)
			data->last_attack = current_time;
	}
}

void	hit_enemy_if_in_range(t_data *data)
{
	int		i;
	float	dx;
	float	dy;
	float	angle_to_enemy;
	float	angle_diff;

	i = -1;
	if (data->enemies)
	{
		while (data->enemies[++i] != NULL)
		{
			if (data->enemies[i]->distance < 2.0
				&& enemy_is_alive(data->enemies[i]))
			{
				dx = data->enemies[i]->x_pos - data->player->x_pos;
				dy = data->enemies[i]->y_pos - data->player->y_pos;
				angle_to_enemy = normalize_rad(atan2(dy, dx));
				angle_diff = angle_difference_rad(angle_to_enemy,
						normalize_rad(data->player->angle));
				if (angle_diff < 0.6)
					data->enemies[i]->state = DYING;
			}
		}
	}
}

void	check_death(t_data *data)
{
	mlx_texture_t	*death_txt;

	if (data->player->hitpoints < 1 && !data->player->is_dead)
	{
		death_txt = mlx_load_png(DEATHSCREEN_PATH);
		if (!death_txt)
			free_all_and_quit(data, "Error\nDeathscreen couldn't load", 79);
		data->deathscreen = mlx_texture_to_image(data->mlx, death_txt);
		if (mlx_image_to_window(data->mlx, data->deathscreen, data->width / 2
				- data->deathscreen->width / 2, data->height / 2
				- data->deathscreen->height / 2) < 0)
			free_all_and_quit(data, "Error on mlx_image_to_window", 11);
		mlx_delete_texture(death_txt);
		data->player->is_dead = 1;
	}
}

void  	check_startscreen(t_data *data)
{
	if (data->startscreen == NULL)
		return ;
	if (mlx_get_time() - data->starttime > 5)
	{
		mlx_delete_image(data->mlx, data->startscreen);
		data->startscreen = NULL;
	}
}

void	ft_hook_hub(void *param)
{
	t_data	*data;

	data = param;
	if (SHOWFPS)
		printf("fps: %.0f\n", 1 / data->mlx->delta_time);
	if (!data->player->is_dead)
		ft_hook_keys(data);
	check_startscreen(data);
	color_whole_image(data->screen, FULL_TRANSPARENT, data->width,
		data->height);
	color_whole_image(data->player->img, FULL_TRANSPARENT,
		data->player->imgwidth, data->player->imgheight);
	draw_player_minimap(data);
	draw_world(data);
	if (data->enemies)
		hook_enemies(data);
	hook_player_animation(data);
	check_death(data);
}

void	hook_mouse_move(double x, double y, void *param)
{
	t_data		*data;
	t_player	*player;
	double		dx;

	(void)y;
	data = param;
	player = data->player;
	if (player->is_dead)
		return ;
	dx = x - data->width / 2;
	player->angle += dx * DEGR * 1.5 * data->speed * MOUSESPEED;
	if (player->angle < 0)
		player->angle += PI2;
	if (player->angle >= PI2)
		player->angle -= PI2;
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}
