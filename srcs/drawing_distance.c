/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_distance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:13:22 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/21 14:57:20 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	increment_offset(t_data *data, t_ray *ray, bool is_vert)
{
	if (is_vert)
	{
		if (ray->y_v > 0 && ray->y_v < data->map_height)
			ray->y_v += ray->y_off;
		if (ray->x_v > 0 && ray->x_v < data->map_width)
			ray->x_v += ray->x_off;
	}
	else
	{
		if (ray->y > 0 && ray->y < data->map_height)
			ray->y += ray->y_off;
		if (ray->x > 0 && ray->x < data->map_width)
			ray->x += ray->x_off;
	}
	ray->dof++;
}

int	check_walls(t_data *data, t_ray *ray, t_map *map, bool is_vert)
{
	if (data->world_map[map->y][map->x] == 1)
		return (1);
	if (data->world_map[map->y][map->x] == 4)
	{
		if (is_vert)
			ray->is_doorv = 1;
		else
			ray->is_doorh = 1;
		return (1);
	}
	return (0);
}

void	calc_distance(t_data *data, t_ray *ray)
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

void	fix_fisheye(t_data *data, t_ray *ray)
{
	float	curr_angle;

	curr_angle = data->player->angle - ray->ang;
	if (curr_angle < 0)
		curr_angle += PI2;
	else if (curr_angle >= PI2)
		curr_angle = curr_angle - (PI2);
	ray->hor_dist *= cosf(curr_angle);
	ray->vert_dist *= cosf(curr_angle);
	ray->dist *= cosf(curr_angle);
}
