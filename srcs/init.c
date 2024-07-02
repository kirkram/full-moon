/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/02 17:52:44 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_data *data)
{
	int	i;

	data->mlx = NULL;
	data->nsew_path = ft_calloc(TEXTURES_AMOUNT, sizeof(char *));
	if (!data->nsew_path)
		map_validation_error("Error: texture path malloc\n", 0, NULL, data);
	i = -1;
	while (++i < TEXTURES_AMOUNT)
		data->nsew_path[i] = NULL;
	data->map_path = NULL;
	data->world_map = NULL;
	data->txtrs = NULL;
	data->swordarm_tx = NULL;
	data->startpos_x = 0;
	data->startpos_y = 0;
	data->floorcolor = 0x0;
	data->ceilingcolor = 0x0;
}

static int	create_fname(char *fname, int i)
{
	char	*num_str;

	num_str = ft_itoa(i + 1);
	if (!num_str)
		return (1);
	ft_strlcpy(fname, "./sprites/sword", 1024);
	ft_strlcat(fname, num_str, 1024);
	ft_strlcat(fname, ".png", 1024);
	free(num_str);
	return (0);
}

int	init_sprites(t_data *data) // free these
{
	int i;
	char fname[1024];

	data->swordarm_tx = (mlx_texture_t **)ft_calloc(PL_FRAMECOUNT + 1,
			sizeof(mlx_texture_t *));
	if (!data->swordarm_tx)
		return (1);
	data->swordarm_tx[PL_FRAMECOUNT] = NULL;
	data->swordarm = NULL;
	i = PL_FRAMECOUNT;
	while (--i >= 0)
	{
		create_fname(fname, i);
		data->swordarm_tx[i] = mlx_load_png(fname);
		if (!data->swordarm_tx[i])
			free_all_and_quit(data, "player sprite load", 26);
	}
	data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[4]);
	mlx_image_to_window(data->mlx, data->swordarm, 1, 1);
	return (0);
}

int	init_player(t_data *data)
{
	if (init_sprites(data))
		return (ft_error("Error on sprite initialization\n", 11));
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
	if (mlx_image_to_window(data->mlx, data->floor, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	color_whole_image(data->floor, data->floorcolor, data->width, data->height);
	data->ceiling = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->ceiling)
		ft_error("Error on mlx_new_image\n", 11);
	if (mlx_image_to_window(data->mlx, data->ceiling, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	color_whole_image(data->ceiling, data->ceilingcolor, data->width,
		data->height / 2);
	mlx_put_string(data->mlx, "CUB3D_0.9", data->width - 100, 1);
	return (0);
}

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
	// int32_t mon_width;
	// int32_t mon_height;
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
		return (11);
	// mlx_get_monitor_size(0, &mon_width, &mon_height);
	// mlx_set_window_pos(data->mlx, mon_width / 3.3, mon_height / 4);
	data->player->angle = rad(NORTH);
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
	int	j;

	// Should use mlx terminate before returning early?
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
	i = -1;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < data->map_width)
		{
			printf("%d ", data->world_map[i][j]);
		}
		printf("\n");
	}
	mlx_cursor_hook(data->mlx, &hook_mouse_move, data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	return (0);
}
