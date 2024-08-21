/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:04:51 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 16:40:57 by klukiano         ###   ########.fr       */
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
	float		darken;

	if (x >= img->width || y >= img->height)
		return (0);
	pixel_index = (y * img->width + x) * sizeof(uint32_t);
	red = img->pixels[pixel_index];
	green = img->pixels[pixel_index + 1];
	blue = img->pixels[pixel_index + 2];
	alpha = img->pixels[pixel_index + 3];
	// temporarily darken them with a static variable;
	darken = 0.6;
	red *= darken;
	green *= darken;
	blue *= darken;
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

// Get the alpha channel.
uint32_t	get_a(uint32_t rgba)
{
	// Move 0 bytes to the right and mask out the first byte.
	return (rgba & 0xFF);
}

void	draw_enemy_onto_canvas(t_enemy *enemy, int dest_x, int dest_y,
		t_data *data)
{
	t_point		sc;
	t_point		ds;
	t_point		f;
	mlx_image_t	*dest;
	mlx_image_t	*src;
	int			ray_index;

	dest = data->screen;
	src = data->enemy_frame[enemy->current_frame];
	sc.y = -1;
	sc.x = -1;
	while (++(sc.x) < (int32_t)src->width)
	{
		ray_index = (dest_x + sc.x * enemy->scale) * (FOV * RESOLUTION)
			/ data->width;
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
							if ((uint32_t)f.x < dest->width
								&& (uint32_t)f.y < dest->height)
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

// Initial version
static void	move_enemy(t_data *data, t_enemy *enemy)
{
	float	move_x;
	float	move_y;
	float	direction_x;
	float	direction_y;
	float	distance;
	float	delta_time;

	delta_time = data->mlx->delta_time;
	if (delta_time > MAX_DELTA)
		delta_time = MAX_DELTA;
	direction_x = enemy->x_target - enemy->x_pos;
	direction_y = enemy->y_target - enemy->y_pos;
	distance = sqrtf(direction_x * direction_x + direction_y * direction_y);
	// printf("distance: %f\n", distance);
	if (distance > 0)
	{
		direction_x /= distance;
		direction_y /= distance;
		move_x = direction_x * ENEMYSPEED * delta_time + enemy->x_pos;
		move_y = direction_y * ENEMYSPEED * delta_time + enemy->y_pos;
		if ((direction_x > 0 && move_x > enemy->x_target) || (direction_x < 0
				&& move_x < enemy->x_target))
			move_x = enemy->x_target;
		if ((direction_y > 0 && move_y > enemy->y_target) || (direction_y < 0
				&& move_y < enemy->y_target))
			move_y = enemy->y_target;
		if (move_x >= 0 && move_x < data->map_width && move_y >= 0
			&& move_y < data->map_height)
		{
			if (data->world_map[(int)enemy->y_pos][(int)move_x] != 1
				&& data->world_map[(int)enemy->y_pos][(int)move_x] != 4)
				enemy->x_pos = move_x;
			if (data->world_map[(int)move_y][(int)enemy->x_pos] != 1
				&& data->world_map[(int)move_y][(int)enemy->x_pos] != 4)
				enemy->y_pos = move_y;
		}
	}
}

void	update_enemy_frame(t_enemy *enemy, t_data *data)
{
	float	a;
	float	b;
	double	prev;
	double	now;
	int		index;

	if (enemy->state == DEAD)
	{
		enemy->current_frame = 61;
		return ;
	}
	a = normalize_degr(enemy->angle / DEGR);
	b = normalize_degr(data->player->angle / DEGR);
	a = normalize_degr(b - a);
	index = (int)((a + 22.5) / 45) % 8;
	index = (8 - index) % 8;
	now = mlx_get_time();
	if (enemy->last_frame == 0.0)
	{
		enemy->current_frame = index;
		enemy->last_frame = now;
		return ;
	}
	prev = enemy->last_frame;
	if (enemy->state == IDLE && (now - prev > 0.7))
	{
		if (enemy->current_frame == index)
			enemy->current_frame = index + 48;
		else
			enemy->current_frame = index;
		enemy->last_frame = now;
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
		return ;
	}
	else if (enemy->state == DYING && now - prev > 0.3)
	{
		if (enemy->current_frame >= 56 && enemy->current_frame < 61)
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
		return (false);
	else
		return (true);
}

static void	step_route(t_enemy *enemy)
{
	int	i;

	i = 0;
	while (enemy->route->coords[i].x != -1)
	{
		enemy->route->coords[i].x = enemy->route->coords[i + 1].x;
		enemy->route->coords[i].y = enemy->route->coords[i + 1].y;
		i++;
	}
}

static void	calculate_enemy_angle(t_enemy *enemy)
{
	float	dx;
	float	dy;
	float	angle_rad;

	dx = enemy->x_pos - enemy->x_target;
	dy = enemy->y_pos - enemy->y_target;
	angle_rad = atan2f(dy, dx);
	enemy->angle = normalize_rad(angle_rad);
}

void	update_enemy(t_enemy *enemy, t_data *data)
{
	int		i;
	t_coord	player_pos;
	t_coord	enemy_pos;

	if (enemy->attack && enemy_is_alive(enemy))
	{
		player_pos.x = data->player->x_pos;
		player_pos.y = data->player->y_pos;
		enemy_pos.x = enemy->x_pos;
		enemy_pos.y = enemy->y_pos;
		if (enemy->route == NULL)
		{
			printf("I saw the player!\n");
			enemy->state = WALKING;
			enemy->route = a_star(enemy_pos, player_pos, data);
			i = 0;
			while (enemy->route->coords[i].x != -1)
			{
				printf("route point %d: x %d y %d\n", i,
					enemy->route->coords[i].x, enemy->route->coords[i].y);
				++i;
			}
			return ;
		}
		if (is_equal(enemy->x_pos, enemy->x_target) && is_equal(enemy->y_pos,
				enemy->y_target))
		{
			printf("Getting new route point.\n");
			if (enemy->route->coords[0].x == -1)
			{
				printf("Route finished.\n");
				free(enemy->route);
				enemy->route = NULL;
				if (enemy->distance > 1.0)
					enemy->route = a_star(enemy_pos, player_pos, data);
				return ;
			}
			else
			{
				enemy->x_target = enemy->route->coords[0].x + 0.5;
				enemy->y_target = enemy->route->coords[0].y + 0.5;
				calculate_enemy_angle(enemy);
				printf("New waypoint: x %f y %f\n", enemy->x_target,
					enemy->y_target);
				printf("Position: x %f y %f\n", enemy->x_pos, enemy->y_pos);
				i = 0;
				while (enemy->route->coords[i].x != -1)
				{
					printf("route point %d: x %d y %d\n", i,
						enemy->route->coords[i].x, enemy->route->coords[i].y);
					++i;
				}
				step_route(enemy);
			}
		}
		// printf("Moving enemy.\n");
		move_enemy(data, enemy);
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
	float	dx;
	float	dy;
	float	rel_ang;

	dx = enemy->x_pos - data->player->x_pos;
	dy = enemy->y_pos - data->player->y_pos;
	enemy->distance = sqrtf(dx * dx + dy * dy);
	rel_ang = atan2(dy, dx) - data->player->angle;
	enemy->rel_angle = atan2f(sinf(rel_ang), cosf(rel_ang));
	if (enemy->rel_angle >= -rad(FOV / 2) && enemy->rel_angle <= rad(FOV / 2))
		enemy->visible = 1;
	else
		enemy->visible = 0;
}

void	hook_enemies(t_data *data)
{
	int i;
	uint32_t screen_x;

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