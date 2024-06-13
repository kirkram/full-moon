/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:39:44 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/10 18:18:28 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_error(char *msg, int	error_code)
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

int	free_2d_int(int **int_arr)
{
	int	i;

	i = 0;
	if (int_arr)
	{
		while (i < MAPHEIGHT)
		{
			free (int_arr[i]);
			i ++;
		}
		free (int_arr);
	}
	return (0);
}
int	color_whole_image(mlx_image_t *img, int color, int width, int height)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(img, x, y, color);
			x ++;
		}
		y ++;
	}
	return (0);
}
