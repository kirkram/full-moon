/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:05:53 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/20 19:30:05 by mburakow         ###   ########.fr       */
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
	data->map_height = 0;
	data->map_width = 0;
	data->txtrs = NULL;
	data->swordarm_tx = NULL;
	data->swordarm = NULL;
	data->last_attack = 0.0;
	data->enemy_ssheet = NULL;
	data->startpos_x = 0;
	data->startpos_y = 0;
	data->floorcolor = 0x0;
	data->ceilingcolor = 0x0;
	data->enemies = NULL;
}

void	init_player_data(t_player *player)
{
	player->img = NULL;
	player->x_pos = 0;
	player->y_pos = 0;
	player->x_pos_mini = 0;
	player->y_pos_mini = 0;
	player->angle = 0;
	player->imgwidth = 0;
	player->imgheight = 0;
}

int	create_fname(char *fname, int i)
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

int	init_player_sprites(t_data *data) // free these
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
	if (init_player_sprites(data))
		return (ft_error("Error on sprite initialization\n", 11));
	data->player->x_pos = data->startpos_x;
	data->player->y_pos = data->startpos_y;
	data->player->imgwidth = data->width;
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

mlx_image_t	*create_enemy_sprite(t_data *data, int sx, int sy)
{
	mlx_image_t	*sprite;
	int			cx;
	int			cy;
	int			sheet_index;
	int			sprite_index;

	sprite = mlx_new_image(data->mlx, ESW, ESH);
	//printf("creating enemy sprite y:%d x:%d\n", sy, sx);
	cy = -1;
	while (++cy < ESH)
	{
		cx = -1;
		while (++cx < ESW)
		{
			sheet_index = ((sy * ESW + cy) * ESSW + (sx * ESW + cx)) * 4;
			sprite_index = (cy * ESW + cx) * 4;
			sprite->pixels[sprite_index
				+ 0] = data->enemy_ssheet->pixels[sheet_index + 0];
			sprite->pixels[sprite_index
				+ 1] = data->enemy_ssheet->pixels[sheet_index + 1];
			sprite->pixels[sprite_index
				+ 2] = data->enemy_ssheet->pixels[sheet_index + 2];
			sprite->pixels[sprite_index
				+ 3] = data->enemy_ssheet->pixels[sheet_index + 3];
		}
	}
	return (sprite);
}

int	init_enemy_frames(t_data *data)
{
	int	i;

	data->enemy_ssheet = mlx_load_png("./sprites/ratman_paletted_b.png");
	if (data->enemy_ssheet == NULL)
		free_all_and_quit(data, "enemy texture loading", 11);
	data->enemy_frame = (mlx_image_t **)ft_calloc(EN_FRAMECOUNT + 1,
			sizeof(mlx_image_t *));
	i = -1;
	while (++i < 64)
	{
		data->enemy_frame[i] = create_enemy_sprite(data, (i % 8), (i / 8));
		if (data->enemy_frame[i] == NULL)
			free_all_and_quit(data, "enemy texture loading", 11);
	}
	data->enemy_frame[EN_FRAMECOUNT] = NULL;
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
