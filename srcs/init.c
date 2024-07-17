/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/17 22:46:22 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_minimap(t_data *data)
{
	mlx_texture_t	*minimap_txt;

	minimap_txt = mlx_load_png(MAPBACKG_PATH);
	if (!minimap_txt)
		return (12);
	minimap_txt->height = data->map_height * data->zoom;
	minimap_txt->width = data->map_width * data->zoom;
	if (minimap_txt->width < data->width && minimap_txt->height < data->height)
	{
		data->minimap_img = mlx_texture_to_image(data->mlx, minimap_txt);
		if (!data->minimap_img)
			return (11);
		if (mlx_image_to_window(data->mlx, data->minimap_img, 0, 0) < 0)
			return (11);
		mlx_delete_texture(minimap_txt);
	}
	data->minimap = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->minimap)
		ft_error("Error on mlx_new_image\n", 11);
	if (mlx_image_to_window(data->mlx, data->minimap, 0, 0) < 0)
		return (ft_error("Error on mlx_image_to_window", 11));
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

int	init_canvases(t_data *data)
{
	data->width = SCREENWIDTH;
	data->height = SCREENHEIGHT;
	data->ceiling = NULL;
	data->minimap = NULL;
	data->zoom = SCREENWIDTH / 150;
	printf("%d\n", PLAYERSIZE);
	data->mlx = mlx_init(data->width, data->height, "CUB3D", false);
	if (!data->mlx)
		return (ft_error("Error on mlx_init\n", 11));
	if (put_background(data) || init_main_screen(data) || init_minimap(data)
		|| init_player(data) || init_enemy_frames(data))
		return (11);
	return (0);
}

void	load_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!data->nsew_path[i] || access(data->nsew_path[i], F_OK))
			free_all_and_quit(data, "can't find texture file", 76);
		data->txtrs[i] = mlx_load_png(data->nsew_path[i]);
		if (!data->txtrs[i])
			free_all_and_quit(data, "error on mlx_load_png", 77);
		if (data->txtrs[i]->width > 4096 || data->txtrs[i]->height > 4096)
			free_all_and_quit(data,
				"image dimensions should be less than 4096 pixels", 78);
	}
	data->txtrs[4] = mlx_load_png(DOOR_PATH);
	if (!data->txtrs[4])
		free_all_and_quit(data, "can't open door file", 75);
	if (data->txtrs[4]->height > 4096 || data->txtrs[4]->width > 4096)
		free_all_and_quit(data, \
		"door dimensions should be less than 4096 pixels", 78);
}

int	init_and_draw(t_data *data)
{
	if (init_canvases(data))
		free_all_and_quit(data, "image initialization", 11);
	data->txtrs = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *)
			* (TEXTURES_AMOUNT + 1));
	if (!data->txtrs)
		free_all_and_quit(data, "texture loading malloc", 11);
	load_textures(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
	draw_minimap(data);
	draw_player_minimap(data);
	draw_rays(data);
	update_enemies(data);
	mlx_cursor_hook(data->mlx, &hook_mouse_move, data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	return (0);
}
