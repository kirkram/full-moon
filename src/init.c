/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/29 18:27:00 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	put_background(t_data *data)
{
	int		x;
	int		y;

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

int	init_window_params(t_data *data)
{
	data->width = SCREENWIDTH;
	data->height = SCREENHEIGHT;
	data->mlx = mlx_init(data->width, data->height, "CUB3D", 0);
	if (!data->mlx)
		ft_error("Error on mlx_init\n", 11);
	data->backg = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->backg)
		ft_error("Error on mlx_new_image\n", 11);
	data->instance = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->instance)
		ft_error("Error on mlx_new_image\n", 11);
	return (0);
}

int	init_window(t_data *data)
{
	if (init_window_params(data))
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (11);
	}
	if (put_background(data))
	{
		mlx_terminate(data->mlx);
		return (11);
	}
	if (mlx_image_to_window(data->mlx, data->instance, 0, 0) < 0)
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (ft_error("Error on mlx_image_to_window", 11));
	}
	return (0);
}


int	init_and_draw(t_data *data)
{
	if(init_window(data))
		return (11);
	draw_minimap(data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}

int	copy_example_map(t_data *data)
{
	int x;
	int y;

	int				world_map[MAPWIDTH][MAPHEIGHT] =
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	data->world_map = malloc(MAPHEIGHT * sizeof(int *));
	if (!data->world_map)
		return (ft_error("Malloc error on int*", 22));
	y = -1;
	while (++y < MAPHEIGHT)
	{
		data->world_map[y] = malloc(MAPWIDTH * sizeof(int));
		if (!data->world_map[y])
			return (ft_error("Malloc error on int", 22));
	}
	y = -1;
	while (++y < MAPHEIGHT)
	{
		x = -1;
		while (++x < MAPWIDTH)
		{
			data->world_map[y][x] = world_map[y][x];
		}
	}
	return (0);
}
