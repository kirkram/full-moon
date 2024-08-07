/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/31 15:03:53 by klukiano         ###   ########.fr       */
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
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

// Get the alpha channel.
uint32_t	get_a(uint32_t rgba)
{
	// Move 0 bytes to the right and mask out the first byte.
	return (rgba & 0xFF);
}

void	draw_enemy_onto_canvas(t_enemy *enemy, int dest_x,
		int dest_y, t_data *data)
{
	t_point		sc;
	t_point		ds;
	t_point		f;
	mlx_image_t	*dest;
	mlx_image_t	*src;
	int			ray_index;

	dest = data->screen;
	src = data->enemy_frame[enemy->current_frame];
	// printf("rendering frame %d\n", enemy->current_frame);
	sc.y = -1;
	sc.x = -1;
	while (++(sc.x) < (int32_t)src->width)
	{
		ray_index = (dest_x + sc.x * enemy->scale) * (FOV * RESOLUTION) / data->width;
		if (ray_index >= 180)
			ray_index = 179;
		if (data->raydis[ray_index] > enemy->distance)
		{
			while (++(sc.y) < (int32_t)src->height)
			{
				sc.color = get_pixel_color(src, (uint32_t)sc.x, (uint32_t)sc.y);
				if (get_a(sc.color) > 0)
				{
					ds.y = -1;
					while (++ds.y < enemy->scale)
                    {
						ds.x = -1;
                        while (++ds.x < enemy->scale)
                        {
                            f.x = dest_x + sc.x * enemy->scale + ds.x;
                            f.y = dest_y + sc.y * enemy->scale + ds.y;
                            if ((uint32_t)f.x < dest->width && (uint32_t)f.y < dest->height)
                            {
                                mlx_put_pixel(dest, f.x, f.y, sc.color);
                            }
                        }
                    }
				}
			}
		}
		sc.y = -1;
	}
}

float normalize_angle(float angle) 
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}

// more complicated when shoot and walk included
void	get_enemy_frame(t_enemy *enemy, t_data *data)
{
	float a;
	float b;
	int	  index;

	// make it relative to the player angle
	a = normalize_angle(enemy->angle / DEGR);
	b = normalize_angle(data->player->angle / DEGR);
	a = normalize_angle(b - a);
	//index = ft_abs(7 - (int)((a - 22.5)  / 45));
	index = (int)((a + 22.5) / 45) % 8;
	index = (8 - index) % 8;
	//printf("player angle: %.0f enemy angle: %.0f\n", b, (enemy->angle / DEGR));
	//printf("angle a: %.0f index: %d\n", a, index);
	enemy->current_frame = index;
}

void	draw_enemy(t_data *data, t_enemy *enemy, uint32_t screen_x)
{
	uint32_t	screen_y;

	if (enemy->distance < 1.0)
		enemy->distance = 1.0;
	enemy->scale = 20.0 / enemy->distance;
	screen_x = screen_x - (ESW * enemy->scale) / 2;
	screen_y = data->mlx->height / 2 - (ESH * enemy->scale) / 2;
	get_enemy_frame(enemy, data);
	draw_enemy_onto_canvas(enemy, screen_x, screen_y, data);
}

void	hook_enemies(t_data *data)
{
	int i;
	float dx;
	float dy;
	float rel_ang;
	uint32_t screen_x;

	i = -1;
	while (data->enemies[++i] != NULL)
	{
		dx = data->enemies[i]->x_pos - data->player->x_pos;
		dy = data->enemies[i]->y_pos - data->player->y_pos;
		data->enemies[i]->distance = sqrtf(dx * dx + dy * dy);
		rel_ang = atan2(dy, dx) - data->player->angle;
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
			screen_x = (uint32_t)((data->enemies[i]->rel_angle + rad(FOV / 2))
					/ rad(FOV) * data->width);
			draw_enemy(data, data->enemies[i], screen_x);
		}
	}
	i = -1;
	while (data->enemies[++i] != NULL)
	{
		find_enemy_rays(data, data->enemies[i]);
	}
}