/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_loadtex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:08:29 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/22 19:02:33 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_and_load_texture(t_data *data, const char *path, int index,
		char *error_msg)
{
	if (!path || access(path, F_OK))
		free_all_and_quit(data, error_msg, 75);
	data->txtrs[index] = mlx_load_png(path);
	if (!data->txtrs[index])
		free_all_and_quit(data, "error on mlx_load_png", 75 + 1);
	if (data->txtrs[index]->width > 4096 || data->txtrs[index]->height > 4096)
		free_all_and_quit(data,
			"image dimensions should be less than 4096 pixels", 75 + 2);
}

void	load_nsew_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		validate_and_load_texture(data, data->nsew_path[i], i,
			(char *)"can't find texture file");
	}
}

void	load_specific_texture(t_data *data, const char *path, int index,
		char *error_msg)
{
	validate_and_load_texture(data, path, index, error_msg);
}

void	load_textures(t_data *data)
{
	load_nsew_textures(data);
	load_specific_texture(data, DOOR_PATH, 4, "can't open door file");
	load_specific_texture(data, FLOOR_PATH, 5, "can't open floor file");
	load_specific_texture(data, SKY_PATH, 6, "can't open sky file");
}
