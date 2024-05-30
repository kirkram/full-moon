/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/30 16:02:35 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	draw_player(t_data *data)
{
	t_player	*player;
	t_point		point;

	player = data->player;
	point.y = -1;
	point.color = YELLOW;
	while (++point.y < player->imgheight)
	{
		point.x = -1;
		while (++point.x < player->imgwidth)
		{
			if (point.x < player->imgwidth && point.y < player->imgheight)
				mlx_put_pixel(player->img, point.x, point.y, point.color);
			else
			{
				ft_error("error in put pixel", 23);
				exit(23);
			}
		}
	}
	return (0);
}

int	init_player(t_data *data)
{
	data->player->x_pos = 0;
	data->player->y_pos = 0;
	data->player->imgwidth = 10;
	data->player->imgheight = 10;
	data->player->img = mlx_new_image(data->mlx, data->player->imgwidth, data->player->imgheight);
	if (!data->player->img)
		ft_error("Error on mlx_new_image\n", 11);
	if (mlx_image_to_window(data->mlx, data->player->img, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	draw_player(data);
	data->player->img->instances[0].x += 175;
	data->player->img->instances[0].y += 175;
	return (0);
}

int	put_background(t_data *data)
{
	int		x;
	int		y;

	data->backg = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->backg)
		ft_error("Error on mlx_new_image\n", 11);
	//returns index of the instance. should it be used?
	if (mlx_image_to_window(data->mlx, data->backg, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			mlx_put_pixel(data->backg, x, y, 0x000011FF);
			x ++;
		}
		y ++;
	}
	mlx_put_string(data->mlx, "CUB3D_0.1", 1100, 1);
	return (0);
}

int	init_minimap(t_data *data)
{
	data->minimap = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->minimap)
		ft_error("Error on mlx_new_image\n", 11);
	if (mlx_image_to_window(data->mlx, data->minimap, 0, 0) < 0)
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (ft_error("Error on mlx_image_to_window", 11));
	}
	return (0);
}

int	init_images(t_data *data)
{
	data->width = SCREENWIDTH;
	data->height = SCREENHEIGHT;
	data->backg = NULL;
	data->minimap = NULL;
	data->mlx = mlx_init(data->width, data->height, "CUB3D", 0);
	if (!data->mlx)
		ft_error("Error on mlx_init\n", 11);
	if (put_background(data))
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (11);
	}
	if (init_minimap(data))
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (11);
	}
	if (init_player(data))
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (11);
	}
	return (0);
}


int	init_and_draw(t_data *data)
{
	if(init_images(data))
		return (11);
	if (data->minimap)
		draw_minimap(data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}

