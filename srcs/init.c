/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/30 10:00:48 by mburakow         ###   ########.fr       */
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
	data->zoom = SCREENWIDTH / 150 + MINIZOOM;
	if (data->zoom > 7)
		data->zoom = 7;
	data->mlx = mlx_init(data->width, data->height, "CUB3D", false);
	if (!data->mlx)
		return (ft_error("Error on mlx_init\n", 11));
	if (put_background(data) || init_main_screen(data) || init_minimap(data)
		|| init_player(data) || init_enemy_frames(data))
		return (11);
	return (0);
}

void	keyhook_loop(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	//(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		free_all_and_quit(data, "Bye!", 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E) && keydata.action == MLX_PRESS)
	{
		printf("Opening door.\n");
		open_door(data);
	}
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
	draw_minimap(data);
	draw_player_minimap(data);
	draw_world(data);
	mlx_cursor_hook(data->mlx, &hook_mouse_move, data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_key_hook(data->mlx, &keyhook_loop, data);
	mlx_loop(data->mlx);
	return (0);
}
