/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/09/15 18:35:31 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* dfm = distance from the middle of the screen
	txt6 is sky.png*/
static void	draw_ceiling(t_data *data, t_ray *ray, int i, float line_w)
{
	float	dfm;
	t_point	*line;
	t_txt	*txt;
	float	line_h;

	line = &data->draw_points;
	txt = &data->draw_txt;
	txt->ptr = data->txtrs[6];
	line_h = data->height / ray->dist * LINESCALE;
	line->y = (data->height - line_h) / 2;
	while (line->y >= 0)
	{
		dfm = data->height / (data->height - 2.0 * line->y);
		find_txt_for_floors_ceiling(data, txt, ray, dfm);
		if (txt->index + 2 < txt->ptr->width * txt->ptr->height
			* txt->ptr->bytes_per_pixel)
			line->color = index_color_floor(txt, ray, dfm, data);
		line->x = line_w * i - 1;
		while (++line->x <= line_w * (i + 1) && line->x < (int32_t)data->width)
			put_pixel(data, line, data->screen);
		line->y--;
	}
}

/* dfm = distance from the middle of the screen
	txt5 is floor.png*/
static void	draw_floor(t_data *data, t_ray *ray, int i, float line_w)
{
	float	dfm;
	t_point	*line;
	t_txt	*txt;

	line = &data->draw_points;
	txt = &data->draw_txt;
	txt->ptr = data->txtrs[5];
	while (line->y < (int32_t)data->height)
	{
		dfm = data->height / (2.0 * line->y - data->height);
		find_txt_for_floors_ceiling(data, txt, ray, dfm);
		if (txt->index + 2 < txt->ptr->width * txt->ptr->height
			* txt->ptr->bytes_per_pixel)
			line->color = index_color_floor(txt, ray, dfm, data);
		line->x = line_w * i - 1;
		while (++line->x <= line_w * (i + 1) && line->x < (int32_t)data->width)
			put_pixel(data, line, data->screen);
		line->y++;
	}
}

static void	draw_walls(t_data *data, t_ray *ray, int i, float line_w)
{
	t_point	*line;
	t_txt	*txt;
	float	line_h;

	line = &data->draw_points;
	txt = &data->draw_txt;
	line_h = init_walls_values(data, ray, &data->draw_txt, &data->draw_points);
	while (line->y < (data->height - line_h) / 2 + line_h
		&& line->y < (int32_t)data->height)
	{
		line->x = line_w * i - 1;
		txt->index = ((uint32_t)txt->y * txt->ptr->width + (uint32_t)txt->x)
			* txt->ptr->bytes_per_pixel;
		if (txt->index + 2 < txt->ptr->width * txt->ptr->height
			* txt->ptr->bytes_per_pixel)
			line->color = index_color(txt, ray, true);
		while (++line->x <= line_w * (i + 1) && line->x < (int32_t)data->width)
			put_pixel(data, line, data->screen);
		line->y++;
		txt->y += txt->y_step;
	}
}

static void	draw_ceiling_walls_floor(t_data *data, t_ray *ray, int i,
		float line_w)
{
	if (DRAW_CEILING)
		draw_ceiling(data, ray, i, line_w);
	else if (DRAW_STARS)
	{
		render_stars(data);
		render_moon(data);
		data->player->prev_angle = data->player->angle;
	}
	assign_texture_to_walls(data, ray, &data->draw_txt);
	draw_walls(data, ray, i, line_w);
	if (DRAW_FLOOR)
		draw_floor(data, ray, i, line_w);
}

void	draw_world(t_data *data)
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
		draw_ceiling_walls_floor(data, ray, i, data->width / ((float)(FOV
					* RESOLUTION)));
		data->raydis[i] = ray->dist;
		ray->ang += DEGR / RESOLUTION;
		angle_outofbounds_check(ray);
	}
}
