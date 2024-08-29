/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:34:30 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 11:25:06 by klukiano         ###   ########.fr       */
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

	if (x >= img->width || y >= img->height)
		return (0);
	pixel_index = (y * img->width + x) * sizeof(uint32_t);
	red = img->pixels[pixel_index];
	green = img->pixels[pixel_index + 1];
	blue = img->pixels[pixel_index + 2];
	alpha = img->pixels[pixel_index + 3];
	red *= 0.6;
	green *= 0.6;
	blue *= 0.6;
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

// Get the alpha channel.
uint32_t	get_a(uint32_t rgba)
{
	return (rgba & 0xFF);
}

void	calculate_enemy_angle(t_enemy *enemy)
{
	float	dx;
	float	dy;
	float	angle_rad;

	dx = enemy->x_pos - enemy->x_target;
	dy = enemy->y_pos - enemy->y_target;
	angle_rad = atan2f(dy, dx);
	enemy->angle = normalize_rad(angle_rad);
}

// update enemy relative angle, distance, visibility
void	get_rel_angle_and_pos(t_enemy *enemy, t_data *data)
{
	float	dx;
	float	dy;
	float	rel_ang;

	dx = enemy->x_pos - data->player->x_pos;
	dy = enemy->y_pos - data->player->y_pos;
	enemy->distance = sqrtf(dx * dx + dy * dy);
	rel_ang = atan2(dy, dx) - data->player->angle;
	enemy->rel_angle = atan2f(sinf(rel_ang), cosf(rel_ang));
	if (enemy->rel_angle >= -rad(FOV / 2) && \
		enemy->rel_angle <= rad(FOV / 2))
		enemy->visible = 1;
	else
		enemy->visible = 0;
}
