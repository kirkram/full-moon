/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:16:03 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/14 20:30:56 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*create_enemy_sprite(t_data *data, int sx, int sy)
{
	mlx_image_t	*sprite;
	t_coord		c;
	int			sheet_index;
	int			sprite_index;

	sprite = mlx_new_image(data->mlx, ESW, ESH);
	c.y = -1;
	while (++c.y < ESH)
	{
		c.x = -1;
		while (++c.x < ESW)
		{
			sheet_index = ((sy * ESW + c.y) * ESSW + (sx * ESW + c.x)) * 4;
			sprite_index = (c.y * ESW + c.x) * 4;
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
	if (DRAW_STARS)
		generate_stars(data);
	if (!data->ceiling)
		ft_error("Error on mlx_new_image\n", 11);
	if (mlx_image_to_window(data->mlx, data->ceiling, 0, 0) < 0)
		ft_error("Error on mlx_image_to_window\n", 11);
	color_whole_image(data->ceiling, data->ceilingcolor, data->width,
		data->height / 2);
	mlx_put_string(data->mlx, "CUB3D_0.9", data->width - 100, 1);
	return (0);
}
