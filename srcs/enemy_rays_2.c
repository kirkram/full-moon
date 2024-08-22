/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rays_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:22:10 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/22 15:08:24 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_distance_enemy(t_ray *ray, t_enemy *enemy)
{
	ray->hor_dist = sqrtf((ray->x - enemy->x_pos) * (ray->x - enemy->x_pos)
			+ (ray->y - enemy->y_pos) * (ray->y - enemy->y_pos));
	ray->vert_dist = sqrtf((ray->x_v - enemy->x_pos) * (ray->x_v - enemy->x_pos)
			+ (ray->y_v - enemy->y_pos) * (ray->y_v - enemy->y_pos));
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

void	draw_minirays_enemy(t_data *data, t_ray *ray, t_enemy *enemy)
{
	t_point	point;
	t_point	dest;

	point.y = enemy->y_pos * data->zoom;
	point.x = enemy->x_pos * data->zoom;
	if (ray->hor_dist < ray->vert_dist && ray->hor_dist != 0)
	{
		dest.x = ray->x * data->zoom;
		dest.y = ray->y * data->zoom;
		point.color = RED;
	}
	else
	{
		dest.x = ray->x_v * data->zoom;
		dest.y = ray->y_v * data->zoom;
		point.color = GREEN;
	}
	drw_line(point, dest, data, data->player->img);
}

int	check_player(t_data *data, t_ray *ray, t_map *map, t_enemy *enemy)
{
	map->x = (int)ray->x;
	map->y = (int)ray->y;
	if (map->x == (int)data->player->x_pos
		&& map->y == (int)data->player->y_pos)
	{
		enemy->attack = true;
		return (1);
	}
	return (0);
}
