/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_vert_rays.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:15:37 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/11 14:41:00 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	vertical_rays_offset(t_data *data, t_ray *ray, int range)
{
	t_player	*player;

	player = data->player;
	ray->ntan = -tan(ray->ang);
	ray->dof = 0;
	if (is_equal(ray->ang, PI_N) || is_equal(ray->ang, PI_S))
	{
		ray->x_v = player->x_pos;
		ray->y_v = player->y_pos;
		ray->dof = range;
	}
	else if (ray->ang < PI_N && ray->ang > PI_S)
	{
		ray->x_v = (int)player->x_pos;
		ray->y_v = (player->x_pos - ray->x_v) * ray->ntan + player->y_pos;
		ray->x_off = -1;
		ray->y_off = -ray->x_off * ray->ntan;
	}
	else if (ray->ang > PI_N || ray->ang < PI_S)
	{
		ray->x_v = (int)player->x_pos + 1;
		ray->y_v = (player->x_pos - ray->x_v) * ray->ntan + player->y_pos;
		ray->x_off = 1;
		ray->y_off = -ray->x_off * ray->ntan;
	}
}

void	vertical_rays(t_data *data, t_ray *ray)
{	
	int		range;
	t_map	map;

	if (data->map_width > data->map_height)
		range = data->map_width;
	else
		range = data->map_height;
	vertical_rays_offset(data, ray, range);
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
				break ;
		}
		increment_offset(data, ray, true);
	}
}
