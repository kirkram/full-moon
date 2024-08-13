/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/13 17:03:44 by mburakow         ###   ########.fr       */
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

// more complicated when shoot and walk included
void	update_enemy_frame(t_enemy *enemy, t_data *data)
{
	float 			a;
	float 			b;
	double			prev;
	double			now;
	int	  			index;

	if (enemy->state == DEAD)
	{
		enemy->current_frame = 61;
		return ;
	}
	// make it relative to the player angle
	a = normalize_degr(enemy->angle / DEGR);
	b = normalize_degr(data->player->angle / DEGR);
	a = normalize_degr(b - a);
	index = (int)((a + 22.5) / 45) % 8;
	index = (8 - index) % 8;
	//printf("player angle: %.0f enemy angle: %.0f\n", b, (enemy->angle / DEGR));
	//printf("angle a: %.0f index: %d\n", a, index);
	now = mlx_get_time();
	if (enemy->last_frame == 0.0)
	{
		enemy->current_frame = index;
		enemy->last_frame = now;
		return ;
	}
	//printf("init uef: %.10f\n", now);
	prev = enemy->last_frame;
	// move here: if (now - prev < smallest change do nothing)
	// or if angle changed enough update frame
	if (enemy->state == IDLE && (now - prev > 0.7))
	{
		if (enemy->current_frame == index)
			enemy->current_frame = index + 48;
		else
			enemy->current_frame = index;
		enemy->last_frame = now;
		//enemy->last_rel_angle = enemy->rel_angle;
		return ;
	}
	else if (enemy->state == WALKING && now - prev > 0.2)
	{
		if (enemy->current_frame == index)
			enemy->current_frame = index + 8;
		else if (enemy->current_frame == index + 8)
			enemy->current_frame = index + 16;
		else if (enemy->current_frame == index + 16)
			enemy->current_frame = index + 32;
		else
			enemy->current_frame = index;
		enemy->last_frame = now;
		//enemy->last_rel_angle = enemy->rel_angle;
		return ;		
	}
	else if (enemy->state == DYING && now - prev > 0.3)
	{
		if (enemy->current_frame >= 56 && enemy->last_frame < 61)
		{
			enemy->current_frame++;
			if (enemy->current_frame == 61)
				enemy->state = DEAD;
		}
		else
			enemy->current_frame = 56;
		enemy->last_frame = now;
		return ; 
	}
}

bool	enemy_is_alive(t_enemy *enemy)
{
	if (enemy->state == DEAD || enemy->state == DYING)
		return false;
	else
		return true;
}

void	update_enemy(t_enemy *enemy, t_data *data)
{
	if (enemy->attack && enemy_is_alive(enemy))
	{
		printf("I saw the player!\n");
		enemy->route = a_star(enemy->x_pos, enemy->y_pos, data->player->x_pos, data->player->y_pos, data);
		enemy->state = WALKING;
	}
}

void	draw_enemy(t_data *data, t_enemy *enemy, uint32_t screen_x)
{
	uint32_t	screen_y;

	if (enemy->distance < 1.0)
		enemy->distance = 1.0;
	enemy->scale = ESCALE / enemy->distance;
	screen_x = screen_x - (ESW * enemy->scale) / 2;
	screen_y = data->mlx->height / 2 - (ESH * enemy->scale) / 2.6;
	draw_enemy_onto_canvas(enemy, screen_x, screen_y, data);
}

// update enemy relative angle, distance, visibility 
void	get_rel_angle_and_pos(t_enemy *enemy, t_data *data)
{
	float dx;
	float dy;
	float rel_ang;

	dx = enemy->x_pos - data->player->x_pos;
	dy = enemy->y_pos - data->player->y_pos;
	enemy->distance = sqrtf(dx * dx + dy * dy);
	rel_ang = atan2(dy, dx) - data->player->angle;
	enemy->rel_angle = atan2f(sinf(rel_ang), cosf(rel_ang));
	if (enemy->rel_angle >= -rad(FOV / 2)
		&& enemy->rel_angle <= rad(FOV / 2))
		enemy->visible = 1;
	else
		enemy->visible = 0;	
}

void	hook_enemies(t_data *data)
{
	int			i;
	uint32_t	screen_x;

	i = -1;
	while (data->enemies[++i] != NULL)
		get_rel_angle_and_pos(data->enemies[i], data);
	sort_enemy_arr(data);
	i = -1;
	while (data->enemies[++i] != NULL)
	{
		update_enemy(data->enemies[i], data);
		update_enemy_frame(data->enemies[i], data);
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