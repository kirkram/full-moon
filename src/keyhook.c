/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/29 18:27:00 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	ft_hook_hub(void *param)
{
	t_data	*data;
	t_data	prev;

	data = param;
	prev = *data;
	ft_hook_movement(data);
	// check_changes_to_data(&prev, data);
}
