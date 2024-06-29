/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/29 14:48:54 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_data *data)
{
	int	i;

	data->nsew_path = malloc(TEXTURES_AMOUNT * sizeof(char *));
	if (!data->nsew_path)
		map_validation_error("Error: texture malloc fail.\n", 0, NULL, data);
	i = -1;
	while (++i < TEXTURES_AMOUNT)
		data->nsew_path[i] = NULL;
	data->map_path = NULL;
	data->world_map = NULL;
	data->startpos_x = 0;
	data->startpos_y = 0;
	data->floorcolor = 0x0;
	data->ceilingcolor = 0x0;
}

static int create_fname(char *fname, int i)
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
	int		i;
	char	fname[1024];

	data->swordarm_tx = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * (PL_FRAMECOUNT + 1));
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
	mlx_image_to_window(data->mlx, data->swordarm, 240, 1);
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
	// returns index of the instance. should it be used?
	if (mlx_image_to_window(data->mlx, data->floor, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	color_whole_image(data->floor, data->floorcolor, data->width, data->height);
	data->ceiling = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->ceiling)
		ft_error("Error on mlx_new_image\n", 11);
	// returns index of the instance. should it be used?
	if (mlx_image_to_window(data->mlx, data->ceiling, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	color_whole_image(data->ceiling, data->ceilingcolor, data->width, data->height / 2);
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

void	load_texture(t_data *data, int i)
{
	if (access(data->nsew_path[i], F_OK))
		free_all_and_quit(data, "can't find texture file", 76);
	data->txtrs[i] = mlx_load_png(data->nsew_path[i]);
	if (!data->txtrs[i])
		free_all_and_quit(data, "error on mlx_load_png", 77);
	if (data->txtrs[i]->width > 4096 || data->txtrs[i]->height > 4096)
		free_all_and_quit(data, "image dimensions should be less than 4096 pixels", 78);
}

void	free_all_and_quit(t_data *data, char *msg, int exitcode)
{
	int	i;

	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	free_textures(data);
	if (data->world_map)
		free_2d_int(data->world_map, data->map_height);
	i = TEXTURES_AMOUNT;
	while (--i >= 0 && data->nsew_path)
	{
		if (data->nsew_path[i])
			free(data->nsew_path[i]);
	}
	free(data->nsew_path);
	if (exitcode)
		printf("Error:");
	exit(ft_error(msg, exitcode));
}

int	init_and_draw(t_data *data)
{
	int	i;
	//Should use mlx terminate before returning early?
	if (init_images(data))
		free_all_and_quit(data, "image initialization", 11);
	data->txtrs = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * (TEXTURES_AMOUNT + 1));
	if (!data->txtrs)
		free_all_and_quit(data, "texture loading malloc", 11);
	i = TEXTURES_AMOUNT;
	while (--i >= 0)
		load_texture(data, i);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
	if (data->minimap)
		draw_minimap(data);
	draw_player(data);
	if(draw_rays(data, data->ray))
		free_all_and_quit(data, "ray drawing", 13);
	mlx_cursor_hook(data->mlx, &hook_mouse_move, data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	mlx_loop(data->mlx);
	return (0);
}
