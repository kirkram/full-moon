/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/17 16:22:35 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_player(t_data *data)
{
	data->player->x_pos = STARTPOS;
	data->player->y_pos = STARTPOS;
	data->player->angle = rad(STARTORIENT);
	data->player->imgwidth = data->width; // or MAPHEIGHT * data->zoom
	data->player->imgheight = data->height;
	data->player->img = mlx_new_image(data->mlx, data->player->imgwidth,
			data->player->imgheight);
	if (!data->player->img)
		return (ft_error("Error on mlx_new_image\n", 11));
	if (mlx_image_to_window(data->mlx, data->player->img, 0, 0) < 0)
		return (ft_error("Error on mlx_image_to_window\n", 11));
	data->player->y_pos_mini = data->player->y_pos * data->zoom;
	data->player->x_pos_mini = data->player->x_pos * data->zoom;
	return (0);
}

int	put_background(t_data *data)
{
	data->floor = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->floor)
		ft_error("Error on mlx_new_image\n", 11);
	// returns index of the instance. should it be used?
	if (mlx_image_to_window(data->mlx, data->floor, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	color_whole_image(data->floor, FLOOR, data->width, data->height);
	data->ceiling = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->ceiling)
		ft_error("Error on mlx_new_image\n", 11);
	// returns index of the instance. should it be used?
	if (mlx_image_to_window(data->mlx, data->ceiling, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	color_whole_image(data->ceiling, CEILING, data->width, data->height / 2);
	mlx_put_string(data->mlx, "CUB3D_0.1", data->width - 100, 1);
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

int	init_main_screen(t_data *data)
{
	data->screen = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->screen)
		return (ft_error("Error on mlx_new_image", 11));
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) < 0)
		return (ft_error("Error on mlx_image_to_window", 11));
	return (0);
}

int	init_images(t_data *data)
{
	data->width = SCREENWIDTH;
	data->height = SCREENHEIGHT;
	data->ceiling = NULL;
	data->minimap = NULL;
	data->zoom = MINIZOOM;
	data->mlx = mlx_init(data->width, data->height, "CUB3D", false);
	if (!data->mlx)
		return (ft_error("Error on mlx_init\n", 11));
	if (put_background(data) || init_main_screen(data) || init_minimap(data)
		|| init_player(data))
	{
		if (data->mlx)
			mlx_terminate(data->mlx);
		return (11);
	}
	return (0);
}

int	load_textures(t_data *data)
{
	char *path;

	path = "./watercolor-paper-texture.png";
	data->texture_1 = mlx_load_png(path);
	if (access(path, F_OK))
		return(ft_error("Cant find file", 123));
	if (!data->texture_1)
		return(ft_error("Error on mlx_load_png", 123));
	mlx_image_t* img = mlx_texture_to_image(data->mlx, data->texture_1);
	// data->texture_1->
	if (!img)
        return(ft_error("failed to transofrm texture to image", 123));
	if (mlx_image_to_window(data->mlx, img, 120, 120) < 0)
		return(ft_error("Error on mlx_image_to_window", 11));
	return (0);
}

int	init_and_draw(t_data *data)
{
	if (init_images(data))
		return (11);
	if(load_textures(data))
		return (123);
	if (data->minimap)
		draw_minimap(data);
	draw_player(data);
	draw_rays(data, data->ray);

	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
