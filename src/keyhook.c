/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/30 15:54:27 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_hook_movement(t_data *data)
{
	t_player	*player;

	player = data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		player->img->instances[0].x -= 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		player->img->instances[0].x += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		player->img->instances[0].y -= 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		player->img->instances[0].y += 1;
}

t_data *reinit_image(t_data *data, mlx_image_t *img)
{
	mlx_delete_image(data->mlx, img);
	img = mlx_new_image(data->mlx, data->width, data->height);
	if (!img)
	{
		ft_error("Error on mlx_new_image (reinit)", 11);
		mlx_close_window(data->mlx);
		return (NULL);
	}
	if (mlx_image_to_window(data->mlx, img, 0, 0) < 0)
	{
		ft_error("Error on mlx_new_image (reinit)", 11);
		mlx_close_window(data->mlx);
		return (NULL);
	}
	return (data);
}

void	ft_hook_hub(void *param)
{
	t_data		*data;
	t_player	prev;

	data = param;
	prev = *(data->player);
	ft_hook_movement(data);;
}
