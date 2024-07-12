/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/12 15:12:24 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	init_column_values(t_data *data, t_ray *ray, t_txt *txt,
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

void	draw_column(t_data *data, t_ray *ray, int i, float line_w)
{
	t_point	line;
	float	line_h;
	t_txt	txt;

	assign_texture_to_ray(data, ray, &txt);
	line_h = init_column_values(data, ray, &txt, &line);
	while (line.y < (data->height - line_h) / 2 + line_h
		&& line.y < (int32_t)data->height)
	{
		line.x = line_w * i - 1;
		txt.index = ((uint32_t)txt.y * txt.ptr->width + (uint32_t)txt.x)
			* txt.ptr->bytes_per_pixel;
		if (txt.index + 2 < txt.ptr->width * txt.ptr->height
			* txt.ptr->bytes_per_pixel)
			line.color = index_color(&txt, ray);
		while (++line.x <= line_w * (i + 1) && line.x < (int32_t)data->width)
			put_pixel(data, &line, data->screen);
		line.y++;
		txt.y += txt.y_step;
	}
}

void	draw_rays(t_data *data)
{
	t_player	*player;
	t_ray		*ray;
	int			i;

	player = data->player;
	ray = data->ray;
	ray->ang = player->angle - rad(FOV / 2);
	angle_outofbounds_check(ray);
	i = -1;
	while (++i < FOV * RESOLUTION)
	{
		ray->is_doorh = 0;
		ray->is_doorv = 0;
		horizontal_rays(data, ray);
		vertical_rays(data, ray);
		calc_distance(data, ray);
		fix_fisheye(data, ray);
		if (DRAWMINIRAYS == 1)
			draw_minirays(data, ray);
		draw_column(data, ray, i, data->width / ((float)(FOV * RESOLUTION)));
		data->raydis[i] = ray->dist;
		ray->ang += DEGR / RESOLUTION;
		angle_outofbounds_check(ray);
	}
}
