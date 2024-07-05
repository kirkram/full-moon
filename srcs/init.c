/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/05 13:54:29 by mburakow         ###   ########.fr       */
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
	data->minimap_img = mlx_texture_to_image(data->mlx, minimap_txt);
	if (!data->minimap_img)
		return (11);
	if (mlx_image_to_window(data->mlx, data->minimap_img, 0, 0) < 0)
		return (11);
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
	data->zoom = MINIZOOM;
	data->mlx = mlx_init(data->width, data->height, "CUB3D", false);
	if (!data->mlx)
		return (ft_error("Error on mlx_init\n", 11));
	if (put_background(data) || init_main_screen(data) || init_minimap(data)
		|| init_player(data) || init_enemy(data))
		return (11);
	return (0);
}

void	load_texture(t_data *data, int i)
{
	if (access(data->nsew_path[i], F_OK))
		free_all_and_quit(data, "can't find texture file", 76);
	data->txtrs[i] = mlx_load_png(data->nsew_path[i]);
	if (!data->txtrs[i])
		free_all_and_quit(data, "error on mlx_load_png", 77);
	if (data->txtrs[i]->width > 4096 || data->txtrs[i]->height > 4096)
		free_all_and_quit(data,
			"image dimensions should be less than 4096 pixels", 78);
}

int	init_and_draw(t_data *data)
{
	int	i;

	if (init_canvases(data))
		free_all_and_quit(data, "image initialization", 11);
	data->txtrs = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *)
			* (TEXTURES_AMOUNT + 1));
	if (!data->txtrs)
		free_all_and_quit(data, "texture loading malloc", 11);
	i = TEXTURES_AMOUNT;
	while (--i >= 0)
		load_texture(data, i);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
	if (draw_minimap(data))
		return (11);
	draw_player(data);
	if (draw_rays(data, data->ray))
		free_all_and_quit(data, "ray drawing", 13);
	draw_sprites(data);
	print_2d_int(data->world_map, data->map_height, data->map_width);
	mlx_cursor_hook(data->mlx, &hook_mouse_move, data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	return (0);
}
