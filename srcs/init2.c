/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:05:53 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/28 18:13:38 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_data *data)
{
	int	i;

	data->mlx = NULL;
	data->nsew_path = ft_calloc(TEXTURES_AMOUNT, sizeof(char *));
	if (!data->nsew_path)
		map_validation_error("Error\nTexture path malloc\n", 0, NULL, data);
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
	player->hitpoints = 4;
	player->is_dead = 0;
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
	int		i;
	char	fname[1024];

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
