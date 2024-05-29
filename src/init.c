/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/29 16:50:31 by klukiano         ###   ########.fr       */
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
	return (0);
}

void	ft_hook_movement(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	// if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	// 	data->shift_x -= 10;
	// else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	// 	data->shift_x += 10;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	// 	data->shift_y -= 10;
	// else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	// 	data->shift_y += 10;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_Z) && data->shift_z > -0.5)
	// 	data->shift_z -= 0.01;
	// else if (mlx_is_key_down(data->mlx, MLX_KEY_X) && data->shift_z < 0.5)
	// 	data->shift_z += 0.01;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_M))
	// 	data->height_col = YELLOW;
	// else if (mlx_is_key_down(data->mlx, MLX_KEY_N))
	// 	data->height_col = MAGENTA;
	//hook_rotation(data);
}

// t_data	*redraw_image(t_data *data)
// {
// 	mlx_delete_image(data->mlx, data->instance);
// 	data->instance = mlx_new_image(data->mlx, data->width, data->height);
// 	if (!data->instance)
// 	{
// 		mlx_close_window(data->mlx);
// 		return (NULL);
// 	}
// 	if (mlx_image_to_window(data->mlx, data->instance, 0, 0) < 0)
// 	{
// 		mlx_close_window(data->mlx);
// 		return (NULL);
// 	}
// 	draw_map(data->map, data);
// 	return (data);
// }

// void	check_changes_to_data(t_data *prev, t_data *data)
// {
// 	if (\
// 	prev->zoom != data->zoom)
// 		redraw_image(data);
// }

// void	ft_hook_hub(void *param)
// {
// 	t_data	*data;
// 	t_data	prev;

// 	data = param;
// 	prev = *data;
// 	ft_hook_movement(data);
// 	check_changes_to_data(&prev, data);
// }



int	init_and_draw(t_data *data)
{
	if(init_window(data))
		return (11);
	if (mlx_image_to_window(data->mlx, data->instance, 0, 0) < 0)
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (ft_error("Error on mlx_image_to_window", 11));
	}
	draw_minimap(data);
	// mlx_loop_hook(data->mlx, &ft_hook_hub, data);
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
