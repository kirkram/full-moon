/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:48:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/27 22:08:49 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *msg, int error_code)
{
	// printf("%s\n", msg);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (error_code);
}

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

void	free_textures(t_data *data)
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
			printf("Freeing enemy %d\n", i);
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
