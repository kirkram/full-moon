/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:39:44 by klukiano          #+#    #+#             */
/*   Updated: 2024/09/15 00:03:23 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec);
}

int	ft_abs(int result)
{
	if (result < 0)
		result = -result;
	return (result);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	is_valid_hex(const char *hex_str)
{
	char	digit;

	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		hex_str += 2;
	while (*hex_str)
	{
		digit = *hex_str;
		if (!ft_isdigit(digit) && !(digit >= 'a' && digit <= 'f')
			&& !(digit >= 'A' && digit <= 'F'))
			return (0);
		hex_str++;
	}
	return (1);
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
