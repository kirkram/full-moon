/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/02 14:55:54 by klukiano         ###   ########.fr       */
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
		player->x_pos_mini -= 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		player->x_pos_mini += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		player->y_pos_mini -= 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		player->y_pos_mini += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_4))
		player->angle -= 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_6))
		player->angle += 1;

}

void	ft_hook_hub(void *param)
{
	t_data		*data;
	t_player	prev;

	data = param;
	prev = *(data->player);
	ft_hook_movement(data);
	if (prev.x_pos_mini != data->player->x_pos_mini || \
	prev.y_pos_mini != data->player->y_pos_mini || \
	prev.angle != data->player->angle)
	{
		mlx_delete_image(data->mlx, data->player->img);
		data->player->img = mlx_new_image(data->mlx, data->player->imgwidth, data->player->imgheight);
		if (!data->player->img)
			ft_error("Error on mlx_new_image\n", 11);
		if (mlx_image_to_window(data->mlx, data->player->img, 0, 0) < 0)
			ft_error("Error on mlx_image_to_window\n", 11);
		draw_player(data);
	}
}
