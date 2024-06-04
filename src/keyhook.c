/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/04 18:16:04 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	ft_hook_movement(t_data *data)
{
	t_player	*player;
	// double		temp_x;
	// double		temp_y;

	player = data->player;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		player->x_pos += SPEED * cos(rad(player->angle));
		player->y_pos += SPEED * sin(rad(player->angle));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		player->x_pos += -SPEED * cos(rad(player->angle));
		player->y_pos += -SPEED * sin(rad(player->angle));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		player->x_pos += -SPEED * cos(rad(player->angle + 90));
		player->y_pos += -SPEED * sin(rad(player->angle + 90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		player->x_pos += SPEED * cos(rad(player->angle + 90));
		player->y_pos += SPEED * sin(rad(player->angle + 90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		player->angle -= (SPEED * 20);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		player->angle += (SPEED * 20);

}
int	refresh_image(t_data *data, mlx_image_t *img, int32_t width, int32_t height)
{
	if (!data || !img || width < 1 || height < 1 || \
	width > data->width || height > data->height)
	{
		printf ("error in refresh_image params\n");
		return (1);
	}
	mlx_delete_image(data->mlx, img);
	img = mlx_new_image(data->mlx, width, height);
	if (!img)
	{
		ft_error("Error on mlx_new_image\n", 11);
		exit (111);
	}
	if (mlx_image_to_window(data->mlx, img, 0, 0) < 0)
	{
		ft_error("Error on mlx_image_to_window\n", 11);
		exit (111);
	}
	return (0);
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
		color_whole_image(data->screen, FULL_TRANSPARENT, data->player->imgwidth, data->player->imgheight);
		draw_screen(data);
		color_whole_image(data->player->img, FULL_TRANSPARENT, data->player->imgwidth, data->player->imgheight);
		draw_player(data);
	}
}
