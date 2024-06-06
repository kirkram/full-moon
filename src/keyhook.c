/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:11:02 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/06 12:29:23 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	loop_360(double angle)
{
	if (angle < 0)
	{
		angle = rad(360) - (-angle);
		//printf("angle 360 0 angle = %f\n", angle);
		angle = (int)angle % 360;
		//printf("angle %%360 = %f\n", angle);
	}
	return (angle);
}

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
		player->x_pos += SPEED * cos(player->angle);
		player->y_pos += SPEED * sin(player->angle);
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		player->x_pos += -SPEED * cos(player->angle);
		player->y_pos += -SPEED * sin(player->angle);
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
		// t_ray		ray;
		// ray.y = (int)(player->y_pos);
		// printf("The y_pos is %f and ray.y up is %f\n", player->y_pos, ray.y);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		player->x_pos += -SPEED * cos(player->angle + rad(90));
		player->y_pos += -SPEED * sin(player->angle + rad(90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		player->x_pos += SPEED * cos(player->angle + rad(90));
		player->y_pos += SPEED * sin(player->angle + rad(90));
		data->player->x_pos_mini = data->player->x_pos * data->zoom;
		data->player->y_pos_mini = data->player->y_pos * data->zoom;
	}
	//SKIPS OVER 0
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		player->angle -= (SPEED / 1.5);
		player->angle = loop_360(player->angle);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		player->angle += (SPEED / 1.5);
		if (player->angle > rad(359))
			player->angle = rad(0.1);
		printf("angle = %d, rad = %f\n", (int)(player->angle * 180 / PI) % 360, player->angle);
	}
}
// int	refresh_image(t_data *data, mlx_image_t *img, int32_t width, int32_t height)
// {
// 	if (!data || !img || width < 1 || height < 1 || \
// 	width > data->width || height > data->height)
// 	{
// 		printf ("error in refresh_image params\n");
// 		return (1);
// 	}
// 	mlx_delete_image(data->mlx, img);
// 	img = mlx_new_image(data->mlx, width, height);
// 	if (!img)
// 	{
// 		ft_error("Error on mlx_new_image\n", 11);
// 		exit (111);
// 	}
// 	if (mlx_image_to_window(data->mlx, img, 0, 0) < 0)
// 	{
// 		ft_error("Error on mlx_image_to_window\n", 11);
// 		exit (111);
// 	}
// 	return (0);
// }

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
