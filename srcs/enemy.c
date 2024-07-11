/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/11 15:01:55 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;
	int			pixel_index;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	pixel_index = (y * img->width + x) * sizeof(uint32_t);
	red = img->pixels[pixel_index];
	green = img->pixels[pixel_index + 1];
	blue = img->pixels[pixel_index + 2];
	alpha = img->pixels[pixel_index + 3];
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

// Get the alpha channel.
uint32_t	get_a(uint32_t rgba)
{
	// Move 0 bytes to the right and mask out the first byte.
	return (rgba & 0xFF);
}

void	draw_enemy_onto_canvas(t_data *data, t_enemy *enemy, int dest_x,
		int dest_y)
{
	t_point		pt;
	mlx_image_t	*dest;
	mlx_image_t	*src;
	int			ray_index;

	dest = data->enemy_img;
	src = data->drawframe;
	pt.y = -1;
	pt.x = -1;
	pt.color = 0;
	while (++(pt.x) < (int32_t)src->width)
	{
		ray_index = (dest_x + pt.x) * (FOV * RESOLUTION) / data->width;
		// printf("ray_index: %d\n", ray_index);
		if (ray_index >= 180)
			ray_index = 179;
		if (data->raydis[ray_index] > enemy->distance)
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
		}
		pt.y = -1;
	}
}

// Here account for not visible: skip drawing: partially visible: draw partially
void	draw_enemy(t_data *data, t_enemy *enemy, uint32_t screen_x)
{
	mlx_image_t	*current;
	int			new_width;
	int			new_height;
	uint32_t	screen_y;

	// printf("screen x: %u\n", screen_x);
	current = data->enemy_frame[enemy->current_frame];
	data->drawframe = NULL;
	data->drawframe = mlx_new_image(data->mlx, current->width, current->height);
	if (!data->drawframe)
		free_all_and_quit(data, "sprite frame draw error", 35);
	ft_memcpy(data->drawframe->pixels, current->pixels, current->width
		* current->height * sizeof(uint32_t));
	// printf("distance was: %f\n", enemy->distance);
	if (enemy->distance < 1.0)
		enemy->distance = 1.0;
	new_height = (int)(ESH * 20 / enemy->distance);
	new_width = (int)(ESW * 20 / enemy->distance);
	if (mlx_resize_image(data->drawframe, new_width, new_height) != 1)
		free_all_and_quit(data, "sprite frame resize error", 35);
	screen_x = screen_x - new_width / 2;
	screen_y = data->mlx->height / 2 - new_height / 2;
	// printf("Enemy sx:%u sy:%u\n", screen_x, screen_y);
	draw_enemy_onto_canvas(data, enemy, screen_x, screen_y);
	mlx_delete_image(data->mlx, data->drawframe);
}

void	hook_enemies(t_data *data)
{
	// relative position of enemy to player
	int i;
	float dx;
	float dy;
	float angle;
	float rel_ang;
	// float       enemy_angle_width;
	uint32_t screen_x;

	i = -1;
	while (data->enemies[++i] != NULL)
	{
		dx = data->enemies[i]->x_pos - data->player->x_pos;
		dy = data->enemies[i]->y_pos - data->player->y_pos;
		data->enemies[i]->distance = sqrtf(dx * dx + dy * dy);
		angle = atan2(dy, dx);
		rel_ang = angle - data->player->angle;
		data->enemies[i]->rel_angle = atan2f(sinf(rel_ang), cosf(rel_ang));
		if (data->enemies[i]->rel_angle >= -rad(FOV / 2)
			&& data->enemies[i]->rel_angle <= rad(FOV / 2))
			data->enemies[i]->visible = 1;
		else
			data->enemies[i]->visible = 0;
	}
	sort_enemy_arr(data);
	i = -1;
	while (data->enemies[++i] != NULL)
	{
		if (data->enemies[i]->visible)
		{
			// enemy_angle_width = atan2f((float)ESW / 2,
					// data->enemies[i]->distance);
			screen_x = (uint32_t)((data->enemies[i]->rel_angle + rad(FOV / 2))
					/ rad(FOV) * data->width);
			// Calculate the start and end angles
			// data->enemies[i]->start_ang = data->enemies[i]->rel_angle
				// - enemy_angle_width;
			// data->enemies[i]->end_ang = data->enemies[i]->rel_angle
				// + enemy_angle_width;
			// Convert angles to corresponding rays
			// data->enemies[i]->start_posx = (int)((data->enemies[i]->start_ang
						// + rad(FOV / 2)) / rad(FOV) * data->width);
			// data->enemies[i]->end_posx = (int)((data->enemies[i]->end_ang
						// + rad(FOV / 2)) / rad(FOV) * data->width);
			draw_enemy(data, data->enemies[i], screen_x);
		}
	}
}