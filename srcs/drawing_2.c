/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:39:14 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/22 13:39:20 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	init_walls_values(t_data *data, t_ray *ray, t_txt *txt,
		t_point *line)
{
	float	line_h;

	line_h = data->height / ray->dist * LINESCALE;
	line->y = (data->height - line_h) / 2;
	txt->y_step = txt->ptr->height / line_h;
	txt->y = 0;
	if (line->y < 0)
	{
		txt->y = fabs(txt->y_step * line->y);
		line->y = 0;
	}
	return (line_h);
}

void	find_txt_for_floors_ceiling(t_data *data, t_txt *txt, t_ray *ray,
		float dfm)
{
	float	weight;

	weight = dfm / ray->dist * 1.7;
	txt->x = ((int)((weight * ray->x + (1.0f - weight) * data->player->x_pos)
				* txt->ptr->width) % txt->ptr->width);
	txt->y = ((int)((weight * ray->y + (1.0f - weight) * data->player->y_pos)
				* txt->ptr->height) % txt->ptr->height);
	txt->index = ((uint32_t)txt->y * txt->ptr->width + (uint32_t)txt->x)
		* txt->ptr->bytes_per_pixel;
}