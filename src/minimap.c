/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:13:41 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/29 18:13:40 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	delta_sign(t_point *dlt, t_point p, t_point dst, t_point *sign)
{
	dlt->x = ft_abs(dst.x - p.x);
	dlt->y = ft_abs(dst.y - p.y);
	if (p.x < dst.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (p.y < dst.y)
		sign->y = 1;
	else
		sign->y = -1;
	if (p.color < dst.color)
		sign->color = 1;
	else
		sign->color = -1;
}

t_point	new_p(int x, int y, t_data *data)
{
	t_point	point;

	point.x = x;
	point.y = y;
	if (data->world_map[y][x] == 1)
		point.color = MAGENTA;
	else if (data->world_map[y][x] == 2)
		point.color = YELLOW;
	else if (data->world_map[y][x] == 3)
		point.color = RED;
	else if (data->world_map[y][x] == 4)
		point.color = BLUE;
	else if (data->world_map[y][x] == 5)
		point.color = GREEN;
	else
		point.color = WHITE;
	point.x *= data->zoom;
	point.y *= data->zoom;
	// point.x += data->shift_x;
	// point.y += data->shift_y;
	// point.x += data->width / 2;
	// point.y += data->height / 5;
	return (point);
}

void	put_pixel(t_data *data, t_point *point)
{
	if (point->x < data->width && point->y < data->height && \
		point->x >= 0 && point->y >= 0)
		mlx_put_pixel(data->instance, point->x, point->y, point->color);
}

void	drw_line(t_point point, t_point dest, t_data *data)
{
	t_point		delta;
	t_point		sign;
	int			error[2];

	delta_sign(&delta, point, dest, &sign);
	error[0] = delta.x - delta.y;
	while (point.x != dest.x || point.y != dest.y)
	{
		put_pixel(data, &point);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
			error[0] -= delta.y;
		if (error[1] > -delta.y)
			point.x += sign.x;
		if (error[1] < delta.x)
			error[0] += delta.x;
		if (error[1] < delta.x)
			point.y += sign.y;
	}
}

void	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	int 	width;
	int		height;

	width = MAPWIDTH;
	height = MAPHEIGHT;
	data->zoom = 10;
	y = 0;
	while (y < MAPHEIGHT)
	{
		x = 0;
		while (x < MAPWIDTH)
		{
			if (x < MAPWIDTH - 1)
				drw_line(new_p(x, y, data), new_p(x + 1, y, data), data);
			if (y < MAPHEIGHT - 1)
				drw_line(new_p(x, y, data), new_p(x, y + 1,  data), data);
			x ++;
		}
		y ++;
	}
}


