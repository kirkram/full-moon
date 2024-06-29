/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:39:44 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/29 13:24:41 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_data *data)
{
    int i;

    if (data->swordarm_tx)
    {
        i = PL_FRAMECOUNT;
        while (--i >= 0)
        {
            if (data->swordarm_tx[i])
                mlx_delete_texture(data->swordarm_tx[i]);
        }
        free(data->swordarm_tx);
    }

    if (data->txtrs)
    {
        i = TEXTURES_AMOUNT;
        while (--i >= 0)
        {
            if (data->txtrs[i])
                mlx_delete_texture(data->txtrs[i]);
        }
        free(data->txtrs);
    }
}

int	ft_error(char *msg, int error_code)
{
	printf("%s\n", msg);
	return (error_code);
}

int	ft_abs(int result)
{
	if (result < 0)
		result = -result;
	return (result);
}

float	rad(float angle)
{
	return (angle * PI / 180);
}

void	print_2d_int(int **int_arr, int rows, int cols)
{
	int y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			dprintf(2, "%d", int_arr[y][x]);
			x++;
		}
		dprintf(2, "\n");
		y++;
	}
	dprintf(2, "\n");
}

int	**copy_2d_int(int **int_arr, int rows, int cols)
{
	int	**new_arr;
	int	y;

	new_arr = malloc(rows * sizeof(int *));
	if (!new_arr)
		exit(ft_error("Malloc error on int**", 22));
	y = -1;
	while (++y < rows)
	{
		new_arr[y] = malloc(cols * sizeof(int));
		if (!new_arr[y])
			exit(ft_error("Malloc error on int**", 22));
		ft_memmove(new_arr[y], int_arr[y], cols * sizeof(int));
	}
	return (new_arr);
}

int	free_2d_int(int **int_arr, int rows)
{
	int	i;

	i = 0;
	if (int_arr)
	{
		while (i < rows)
		{
			free(int_arr[i]);
			i++;
		}
		free(int_arr);
	}
	return (0);
}

int	color_whole_image(mlx_image_t *img, int color, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

