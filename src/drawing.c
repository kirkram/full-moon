/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/02 14:57:12 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double rad(double angle)
{
	return (angle * PI / 180);
}

void	apply_rotation(t_data *data, t_point *point, int x, int y)
{
	t_player	*player;
	t_point		temp;

	player = data->player;
	temp.x = x * cos(rad(player->angle)) - y * sin(rad(player->angle));
	temp.y = y * cos(rad(player->angle)) + x * sin(rad(player->angle));
	point->x = temp.x;
	point->y = temp.y;
}
int	draw_player(t_data *data)
{
	t_player	*player;
	t_point		point;

	player = data->player;
	int		direction_w = 4;
	int		direction_h = 7;
	int		pl_w = 6;
	int		pl_h = 12;

	int		x;
	int		y;

	//draw direction red
	y = -1;
	while (++y < direction_h)
	{
		x = 3;
		while (x < direction_w)
		{
			point.x = x;
			point.y = y;
			apply_rotation(data, &point, x, y);
			if (x >= 0 && y >= 0 && \
			x < player->imgwidth && y < player->imgheight)
				mlx_put_pixel(player->img, player->x_pos_mini + point.x, \
				player->y_pos_mini + point.y, RED);
			x ++;
		}
	}
	//draw player yellow
	y = direction_h - 1;
	while (++y < pl_h)
	{
		x = -1;
		while (++x < pl_w)
		{
			point.x = x;
			point.y = y;
			apply_rotation(data, &point, x, y);
			if (x < player->imgwidth && y < player->imgheight)
				mlx_put_pixel(player->img, player->x_pos_mini + point.x, \
				player->y_pos_mini + point.y, YELLOW);
			else
			{
				ft_error("Error on put pixel", 23);
				exit(23);
			}
		}
	}
	return (0);
}

void	put_pixel(t_data *data, t_point *point, mlx_image_t *img)
{
	if (point->x < data->width && point->y < data->height && \
		point->x >= 0 && point->y >= 0)
		mlx_put_pixel(img, point->x, point->y, point->color);
}
