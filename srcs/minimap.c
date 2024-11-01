/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:13:41 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/28 17:17:22 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		point.color = GRAY;
	else if (data->world_map[y][x] == 2)
	{
		point.color = WHITE;
	}
	else if (data->world_map[y][x] == 3)
		point.color = RED;
	else if (data->world_map[y][x] == 4)
		point.color = BLUE;
	else if (data->world_map[y][x] == 5)
		point.color = GREEN;
	else
		point.color = YELLOW;
	point.x *= data->zoom;
	point.y *= data->zoom;
	return (point);
}

void	drw_line(t_point point, t_point dest, t_data *data, mlx_image_t *img)
{
	t_point	delta;
	t_point	sign;
	int		error[2];

	delta_sign(&delta, point, dest, &sign);
	error[0] = delta.x - delta.y;
	while (point.x != dest.x || point.y != dest.y)
	{
		put_pixel(data, &point, img);
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
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (x < data->map_width - 1)
				drw_line(new_p(x, y, data), new_p(x + 1, y, data), data,
					data->minimap);
			if (y < data->map_height - 1)
				drw_line(new_p(x, y, data), new_p(x, y + 1, data), data,
					data->minimap);
			x++;
		}
		y++;
	}
}
