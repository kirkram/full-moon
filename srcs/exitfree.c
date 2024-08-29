/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:48:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 11:18:46 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_validation_error(char *msg, int rows, char *line, t_data *data)
{
	if (line != NULL)
		free(line);
	if (data->world_map)
	{
		free_2d_int(data->world_map, rows);
		data->world_map = NULL;
	}
	free_all_and_quit(data, msg, 25);
}

static void	free_textures_sword(t_data *data)
{
	int	i;

	if (data->swordarm_tx != NULL)
	{
		i = PL_FRAMECOUNT;
		while (--i >= 0)
		{
			if (data->swordarm_tx[i])
				mlx_delete_texture(data->swordarm_tx[i]);
		}
		if (data->swordarm_tx)
			free(data->swordarm_tx);
	}
}

void	free_textures(t_data *data)
{
	int	i;

	free_textures_sword(data);
	if (data->txtrs != NULL)
	{
		i = TEXTURES_AMOUNT;
		while (--i >= 0)
		{
			if (data->txtrs[i])
				mlx_delete_texture(data->txtrs[i]);
		}
		if (data->txtrs)
			free(data->txtrs);
	}
	if (data->enemy_ssheet != NULL)
		mlx_delete_texture(data->enemy_ssheet);
}

void	free_enemies(t_data *data)
{
	int	i;

	i = -1;
	if (data->enemies != NULL)
	{
		while (data->enemies[++i] != NULL)
		{
			if (data->enemies[i]->route != NULL)
			{
				free(data->enemies[i]->route->coords);
				free(data->enemies[i]->route);
			}
			free(data->enemies[i]);
			data->enemies[i] = NULL;
		}
		free(data->enemies);
		data->enemies = NULL;
	}
}

void	free_all_and_quit(t_data *data, char *msg, int exitcode)
{
	int	i;

	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	free_textures(data);
	free_enemies(data);
	if (data->world_map)
		free_2d_int(data->world_map, data->map_height);
	i = TEXTURES_AMOUNT;
	while (--i >= 0 && data->nsew_path)
	{
		if (data->nsew_path[i])
			free(data->nsew_path[i]);
	}
	if (data->nsew_path)
		free(data->nsew_path);
	exit(ft_error(msg, exitcode));
}
