/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:57:28 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/27 17:33:20 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_data *data)
{
	int	i;

	data->nsew_path = malloc((TEXTURES_AMOUNT + 1) * sizeof(char *));
	if (!data->nsew_path)
		map_validation_error("Error: texture malloc fail.\n", 0, NULL, data);
	i = -1;
	while (++i <= TEXTURES_AMOUNT)
		data->nsew_path[i] = NULL;
	data->map_path = NULL;
	data->world_map = NULL;
	data->startpos_x = 0;
	data->startpos_y = 0;
}

int	init_sprites(t_data *data) // free these
{
	int		i;
	char	*tmp;
	char	*fname;

	i = 11;
	data->swordarm_tx = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * i + 1);
	if (!data->swordarm_tx)
		return (1);
	data->swordarm_tx[i] = NULL;
	//data->swordarm = (mlx_image_t **)malloc(sizeof(mlx_image_t *) * i + 1);
	//if (!data->swordarm)
	//	return (1);
	data->swordarm = NULL;
	while (--i >= 0)
	{
		tmp = ft_strjoin("./sprites/sword", ft_itoa(i + 1));
		fname = ft_strjoin(tmp, ".png");
		data->swordarm_tx[i] = mlx_load_png(fname);
		printf("Loading sprite file: %s\n", fname);
		free(tmp);
		tmp = NULL;
		free(fname);
		fname = NULL;
		if (!data->swordarm_tx[i])
			return (1);
		//data->swordarm[i] = mlx_texture_to_image(data->mlx, data->swordarm_tx[i]);
		//if (!data->swordarm[i])
		//	return (1);
		printf("Initialized sprite %d\n", i);
	}
	data->swordarm = mlx_texture_to_image(data->mlx, data->swordarm_tx[10]);
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

void	free_and_quit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TEXTURES_AMOUNT)
		mlx_delete_texture(data->txtrs[i]);
	free_2d_int(data->world_map, data->map_height);
	mlx_terminate(data->mlx);
	i = -1;
	while (data->nsew_path && data->txtrs && ++i < TEXTURES_AMOUNT)
	{
		free(data->nsew_path[i]);
	}
	free(data->txtrs);
	free(data->nsew_path);
}

int	init_and_draw(t_data *data)
{
	int	i;
	//Should use mlx terminate before returning early?
	if (init_images(data))
		return (11);
	i = -1;
	data->txtrs = (mlx_texture_t **)malloc(TEXTURES_AMOUNT * sizeof(mlx_texture_t *));
	while (++i < TEXTURES_AMOUNT)
	{
		data->txtrs[i] = malloc(sizeof(mlx_texture_t *));
		if (load_texture(data->nsew_path[i], &data->txtrs[i]))
			return (123);
	}
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, data->width / 2, data->height / 2);
	if (data->minimap)
		draw_minimap(data);
	draw_player(data);
	if(draw_rays(data, data->ray))
		mlx_close_window(data->mlx);
	mlx_cursor_hook(data->mlx, &hook_mouse_move, data);
	mlx_loop_hook(data->mlx, &ft_hook_hub, data);
	while (!mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_loop(data->mlx);
	return (0);
}
