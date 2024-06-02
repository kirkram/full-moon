/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/02 13:18:44 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	draw_player(t_data *data)
{
	t_player	*player;
	t_point		point;

	player = data->player;
	int		direction_w = 4;
	int		direction_h = 7;
	int		pl_w = 6;
	int		pl_h = 12;

	point.y = -1;
	while (++point.y < direction_h)
	{
		point.x = 3;
		while (point.x < direction_w)
		{
			if (point.x < player->imgwidth && point.y < player->imgheight)
				mlx_put_pixel(player->img, player->x_pos_mini + point.x, \
				player->y_pos_mini + point.y, RED);
			else
			{
				ft_error("Error on put pixel", 23);
				exit(23);
			}
			point.x ++;
		}
	}
	point.y = direction_h - 1;
	while (++point.y < pl_h)
	{
		point.x = -1;
		while (++point.x < pl_w)
		{
			if (point.x < player->imgwidth && point.y < player->imgheight)
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
