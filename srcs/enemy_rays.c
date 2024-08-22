/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:21:15 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/22 17:23:37 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	vertical_rays_offset_enemy(t_ray *ray, int range, t_enemy *enemy)
{
	ray->ntan = -tan(ray->ang);
	ray->dof = 0;
	if (is_equal(ray->ang, PI_N) || is_equal(ray->ang, PI_S))
	{
		ray->x_v = enemy->x_pos;
		ray->y_v = enemy->y_pos;
		ray->dof = range;
	}
	else if (ray->ang < PI_N && ray->ang > PI_S)
	{
		ray->x_v = (int)enemy->x_pos;
		ray->y_v = (enemy->x_pos - ray->x_v) * ray->ntan + enemy->y_pos;
		ray->x_off = -1;
		ray->y_off = -ray->x_off * ray->ntan;
	}
	else if (ray->ang > PI_N || ray->ang < PI_S)
	{
		ray->x_v = (int)enemy->x_pos + 1;
		ray->y_v = (enemy->x_pos - ray->x_v) * ray->ntan + enemy->y_pos;
		ray->x_off = 1;
		ray->y_off = -ray->x_off * ray->ntan;
	}
}

void	vertical_rays_enemy(t_data *data, t_ray *ray, t_enemy *enemy)
{
	int		range;
	t_map	map;

	range = enemy->dof;
	vertical_rays_offset_enemy(ray, range, enemy);
	while (ray->dof < range)
	{
		map.y = (int)ray->y_v;
		map.x = (int)ray->x_v;
		if (ray->ang > PI_S && ray->ang < PI_N)
			map.x -= 1;
		if (map.x < 0)
			break ;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width
			&& map.x >= 0)
		{
			if (check_walls(data, ray, &map, true))
				return ;
			if (check_player(data, ray, &map, enemy))
				break ;
		}
		increment_offset(data, ray, true);
	}
}

static void	horizontal_rays_offset_enemy(t_ray *ray, int range, t_enemy *enemy)
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

void	horizontal_rays_enemy(t_data *data, t_ray *ray, t_enemy *enemy)
{
	t_map		map;
	int			range;

	ray->dof = 0;
	range = enemy->dof;
	horizontal_rays_offset_enemy(ray, range, enemy);
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
				return ;
			if (check_player(data, ray, &map, enemy))
				return ;
		}
		increment_offset(data, ray, false);
	}
}

void	find_enemy_rays(t_data *data, t_enemy *enemy)
{
	t_ray		*enemy_ray;
	int			i;

	enemy_ray = &enemy->ray;
	enemy_ray->ang = enemy->angle - rad(FOV / 2 / 2);
	enemy_ray->ang -= PI;
	enemy->dof = 5;
	angle_outofbounds_check(enemy_ray);
	i = -1;
	while (++i < FOV / 2)
	{
		horizontal_rays_enemy(data, enemy_ray, enemy);
		vertical_rays_enemy(data, enemy_ray, enemy);
		calc_distance_enemy(enemy_ray, enemy);
		draw_minirays_enemy(data, enemy_ray, enemy);
		enemy_ray->ang += DEGR * 2;
		angle_outofbounds_check(enemy_ray);
	}
}
