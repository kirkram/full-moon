/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_hor_rays.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:15:04 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/11 14:41:51 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	horizontal_rays_offset(t_data *data, t_ray *ray, int range)
{
	t_player	*player;

	player = data->player;
	ray->atan = -1 / tanf(ray->ang);
	if (is_equal(ray->ang, 0.0) || is_equal(ray->ang, PI))
	{
		ray->y = player->y_pos;
		ray->x = player->x_pos;
		ray->dof = range;
	}
	else if (ray->ang > PI)
	{
		ray->y = (int)(player->y_pos);
		ray->x = (player->y_pos - ray->y) * ray->atan + player->x_pos;
		ray->y_off = -1;
		ray->x_off = -ray->y_off * ray->atan;
	}
	else if (ray->ang < PI)
	{
		ray->y = (int)(player->y_pos) + 1;
		ray->x = (player->y_pos - ray->y) * ray->atan + player->x_pos;
		ray->y_off = 1;
		ray->x_off = -ray->y_off * ray->atan;
	}
}

void	horizontal_rays(t_data *data, t_ray *ray)
{
	t_map		map;
	int			range;

	ray->dof = 0;
	range = data->map_height;
	if (data->map_width > data->map_height)
		range = data->map_width;
	horizontal_rays_offset(data, ray, range);
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
		}
		increment_offset(data, ray, false);
	}
}
