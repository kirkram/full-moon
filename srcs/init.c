/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/25 13:54:05 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_data *data)
{
	data->map_path = NULL;
	data->world_map = NULL;
	data->startpos_x = 0;
	data->startpos_y = 0;
}

int	init_player(t_data *data)
{
	data->player->x_pos = data->startpos_x;
	data->player->y_pos = data->startpos_y;
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

int	load_texture(char *path, mlx_texture_t **txt)
{
	*txt = mlx_load_png(path);
	
	if (!(*txt))
		return(ft_error("Error on mlx_load_png", 123));
	if (access(path, F_OK))
		return(ft_error("Cant find file", 123));
	if ((*txt)->width > 4096 || (*txt)->height > 4096)
		return(ft_error("The image dimensions should be less than 4096 pixels", 78));
	return (0);
}

int	init_and_draw(t_data *data)
{
	//Should use mlx terminate before returning early?
	if (init_images(data))
		return (11);
	data->nsew_path = malloc((TEXTURES_AMOUNT + 1) * sizeof(char *));
	if (!data->nsew_path)
		return (12);
	int i = -1;
	//ASSIGN EARLIER FROM THE MAP
	while (++i < TEXTURES_AMOUNT)
	{
		data->nsew_path[i] = malloc(666);
		ft_strlcpy(data->nsew_path[i], TEXTURE_PATH, -1);
	}
	data->nsew_path[i] = NULL;
	// 1 extra for null
	i = -1;
	
	while (++i < TEXTURES_AMOUNT)
	{
		data->txtrs[i] = NULL;
		if (load_texture(data->nsew_path[i], &data->txtrs[i]))
			return (123);
	}
	// data->txt_n = mlx_load_png(TEXTURE_PATH);
	// if (!data->txt_n)
	// 	return (123);
	// data->txt_n = mlx_load_png(data->nsew_path[0]);
	if (data->minimap)
		draw_minimap(data);
	draw_player(data);
	draw_rays(data, data->ray);

	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	
	// int j = 1;
	// while (j < TEXTURES_AMOUNT)
	// 	mlx_delete_texture(data->txtrs[j]);
	mlx_terminate(data->mlx);
	return (0);
}
