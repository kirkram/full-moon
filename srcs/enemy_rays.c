/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:21:15 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/30 19:45:30 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	horizontal_rays_offset_enemy(t_data *data, t_ray *ray, int range, t_enemy *enemy)
{
	ray->atan = -1 / tanf(ray->ang);
	if (is_equal(ray->ang, 0.0) || is_equal(ray->ang, PI))
	{
		ray->y = enemy->y_pos;
		ray->x = enemy->x_pos;
		ray->dof = range;
	}
	else if (ray->ang > PI)
	{
		ray->y = (int)(enemy->y_pos);
		ray->x = (enemy->y_pos - ray->y) * ray->atan + enemy->x_pos;
		ray->y_off = -1;
		ray->x_off = -ray->y_off * ray->atan;
	}
	else if (ray->ang < PI)
	{
		ray->y = (int)(enemy->y_pos) + 1;
		ray->x = (enemy->y_pos - ray->y) * ray->atan + enemy->x_pos;
		ray->y_off = 1;
		ray->x_off = -ray->y_off * ray->atan;
	}
}

void	horizontal_rays_enemy(t_data *data, t_ray *ray, t_enemy* enemy)
{
	t_map		map;
	int			range;

	ray->dof = 0;
	range = enemy->dof;
	horizontal_rays_offset_enemy(data, ray, range, enemy);
	while (ray->dof < range)
	{
		map.y = (int)ray->y;
		map.x = (int)ray->x;
		if (ray->ang > PI)
			map.y -= 1;
		if (map.y < 0)
			break ;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width
			&& map.x >= 0)
		{
			if (check_walls(data, ray, &map, false))
				break ;
			else if (check_player(data, ray, &map))
			{
				enemy->attack = true;
			}
		}
		increment_offset(data, ray, false);
	}
}

void	calc_distance_enemy(t_data *data, t_ray *ray)
{
	t_player	*player;

	player = data->player;
	ray->hor_dist = sqrtf((ray->x - player->x_pos) * (ray->x - player->x_pos)
			+ (ray->y - player->y_pos) * (ray->y - player->y_pos));
	ray->vert_dist = sqrtf((ray->x_v - player->x_pos) * (ray->x_v
				- player->x_pos) + (ray->y_v - player->y_pos) * (ray->y_v
				- player->y_pos));
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist
			&& ray->vert_dist != 0))
	{
		ray->dist = ray->vert_dist;
		ray->x = ray->x_v;
		ray->y = ray->y_v;
	}
	else
		ray->dist = ray->hor_dist;
}

void	find_enemy_rays(t_data *data, t_enemy *enemy)
{
	t_ray		*enemy_ray;
	int			i;

	enemy_ray = &enemy->ray;
	enemy_ray->ang = enemy->angle - rad(FOV / 2);
	//enemy->attack = true //should be in the attack state  for some time or until death
	angle_outofbounds_check(enemy_ray);
	i = -1;
	while (++i < FOV * RESOLUTION)
	{
		enemy_ray->is_doorh = 0;
		enemy_ray->is_doorv = 0;
		horizontal_rays_enemy(data, enemy_ray, enemy);
		vertical_rays_enemy(data, enemy_ray);
		calc_distance(data, enemy_ray);
		// fix_fisheye(data, enemy_ray);
		if (DRAWMINIRAYS == 1)
			draw_minirays(data, enemy_ray);
		draw_column(data, enemy_ray, i, data->width / ((float)(FOV * RESOLUTION)));
		data->raydis[i] = enemy_ray->dist;
		enemy_ray->ang += DEGR / RESOLUTION;
		angle_outofbounds_check(enemy_ray);
	}
}