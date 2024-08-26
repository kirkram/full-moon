/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/26 11:30:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook_keys(t_data *data)
{
	double	current_time;

	data->speed = 0.003 / (1 / data->mlx->delta_time / 1000);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		free_all_and_quit(data, "Bye!", 0);
	movement_loop(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ENTER))
	{
		current_time = mlx_get_time();
		if (current_time - data->last_attack >= ATTACK_SPEED)
			data->last_attack = current_time;
	}
}

// Calculate the smallest difference between two angles
float	angle_difference_rad(float angle1, float angle2)
{
	float	diff;

	diff = fabs(angle1 - angle2);
	if (diff > PI)
		diff = 2 * PI - diff;
	return (diff);
}


// printf("Angle %.10f Distance %.10f\n", angle_diff,
//					data->enemies[i]->distance);
void	hit_enemy_if_in_range(t_data *data)
{
	int		i;
	float	dx;
	float	dy;
	float	angle_to_enemy;
	float	angle_diff;

	i = -1;
	printf("Determining hit.\n");
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

void	ft_hook_hub(void *param)
{
	t_data	*data;

	data = param;
	// printf("fps: %.0f\n", 1 / data->mlx->delta_time);
	ft_hook_keys(data);
	color_whole_image(data->screen, FULL_TRANSPARENT, data->width,
		data->height);
	color_whole_image(data->player->img, FULL_TRANSPARENT,
		data->player->imgwidth, data->player->imgheight);
	draw_player_minimap(data);
	draw_world(data);
	if (data->enemies)
		hook_enemies(data);
	hook_player_animation(data);
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
	player->angle += dx * DEGR * 1.5 * data->speed * MOUSESPEED;
	if (player->angle < 0)
		player->angle += PI2;
	if (player->angle >= PI2)
		player->angle -= PI2;
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
}

/*
void	draw_player_onto_canvas(t_data *data, mlx_image_t *frame, int dest_x,
		int dest_y)
{
	t_point		pt;
	mlx_image_t	*dest;
	mlx_image_t	*src;

	color_whole_image(data->player->img, FULL_TRANSPARENT,
		data->player->imgwidth, data->player->imgheight);
	dest = data->player->img;
	src = frame;
	pt.y = -1;
	pt.x = -1;
	pt.color = 0;
	while (++(pt.x) < (int32_t)src->width)
	{
		while (++(pt.y) < (int32_t)src->height)
		{
			pt.color = get_pixel_color(src, (uint32_t)pt.x, (uint32_t)pt.y);
			if (get_a(pt.color) > 0)
			{
				if ((dest_x + pt.x) >= 0 && (uint32_t)(dest_x
						+ pt.x) < dest->width && (dest_y + pt.y) >= 0
					&& (uint32_t)(dest_y + pt.y) < dest->height)
				{
					mlx_put_pixel(dest, dest_x + pt.x, dest_y + pt.y,
						pt.color);
				}
			}
		}
		pt.y = -1;
	}
}

void	hook_animation(t_data *data)
{
	static double	last_update = 0;
	static int		frame = 0;
	double			current_time;

	mlx_img
	current_time = mlx_get_time();
	if ((current_time - last_update >= ANIMATION_SPEED / 4) && (current_time
			- data->last_attack >= ANIMATION_SPEED))
	{
		mlx_delete_image(data->mlx, data->swordarm);
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
			frame = 7;
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 8))
			frame = 8;
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 6))
			frame = 9;
		else
			frame = 10;
		mlx_image_to_window(data->mlx, data->swordarm[frame], data->width
			* 0.19, 1);
	}
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (current_time - data->last_attack >= ANIMATION_SPEED)
			attack_animation(data);
	}
}

// Both are slower

void	hook_animation(t_data *data)
{
	static double	last_update = 0;
	static int		frame = 0;
	double			current_time;

	current_time = mlx_get_time();
	if (current_time - data->last_attack < ANIMATION_SPEED)
	{
		if (current_time - data->last_attack < (ANIMATION_SPEED) / 10)
			frame = 7;
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 8))
			frame = 8;
		else if (current_time - data->last_attack < (ANIMATION_SPEED / 6))
			frame = 9;
		else
			frame = 10;
		draw_player_onto_canvas(data, data->swordarm[frame], data->width * 0.19,
			1);
	}
	else if (current_time - last_update >= ANIMATION_SPEED / 4)
	{
		if (frame > 4)
			frame = 0;
		frame++;
		if (frame > 3)
			frame = 0;
		draw_player_onto_canvas(data, data->swordarm[frame], data->width * 0.45,
			1);
		last_update = mlx_get_time();
	}
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (current_time - data->last_attack >= ANIMATION_SPEED)
			attack_animation(data);
	}
	mlx_image_to_window(data->mlx, data->player->img, 1, 1);
}
*/