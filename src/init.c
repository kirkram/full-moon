/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/30 13:03:53 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	init_player(t_data *data)
// {
// 	data->player->x_pos = 24;
// 	data->player->y_pos = 24;

// 	data->player->img = mlx_new_image(data->mlx, data->width, data->height);
// 	if (!data->player->img)
// 		ft_error("Error on mlx_new_image\n", 11);
// 	if (mlx_image_to_window(data->mlx, data->player->img, 24, 24) < 0)
// 		ft_error("Error on mlx_image_to_window\n", 11);
// 	//mlx_put_pixel(data->player.img, data->player.x_pos, data->player.y_pos, 0xFFFF00FF);
// 	return (0);
// }

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
	// if (init_player(data))
	// {
	// 	if (data->mlx)
	// 		mlx_terminate(data->mlx);
	// 	return (11);
	// }
	return (0);
}


int	init_and_draw(t_data *data)
{
	if(init_images(data))
		return (11);
	draw_minimap(data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}

