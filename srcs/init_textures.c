/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:04:31 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/22 15:05:51 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_texture_loading(t_data *data, mlx_texture_t *txt,
	char *txt_name)
{
	if (!txt)
	{
		ft_error(txt_name, 1);
		free_all_and_quit(data, "can't open texture file", 75);
	}
	if (txt->height > 4096 || txt->width > 4096)
	{
		ft_error(txt_name, 1);
		free_all_and_quit(data,
			"dimensions should \
				be less than 4096 pixels", 78);
	}
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
	check_texture_loading(data, data->txtrs[4], "Door texture error:");
	data->txtrs[5] = mlx_load_png(FLOOR_PATH);
	check_texture_loading(data, data->txtrs[5], "Floor texture error:");
	data->txtrs[6] = mlx_load_png(SKY_PATH);
	check_texture_loading(data, data->txtrs[6], "Sky texture error:");
}
