/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:48:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/07/02 17:54:31 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *msg, int error_code)
{
	printf("%s\n", msg);
	return (error_code);
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
