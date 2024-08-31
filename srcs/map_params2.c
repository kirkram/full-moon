/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_params2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:36:06 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/31 15:39:57 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_all_numeric(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

static int	rgb_validation_loop(int len, unsigned int *rgb, char **value_array)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (!is_all_numeric(value_array[i]))
			return (1);
		rgb[i] = ft_atoi(value_array[i]);
	}
	i = -1;
	while (++i < len)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
	}
	return (0);
}

unsigned int	read_rgb_color_value(char *line, t_data *data)
{
	char			**value_array;
	int				len;
	unsigned int	rgb[3];

	value_array = ft_split((line + 2), ',');
	len = 0;
	while (value_array[len] != NULL)
		len++;
	if (len != 3)
		map_validation_error("Error\nInvalid map parameter 1", 0, line, data);
	if (rgb_validation_loop(len, rgb, value_array))
	{
		free_2d_char(value_array);
		map_validation_error("Error\nInvalid map parameter 3", 0, line, data);
	}
	free_2d_char(value_array);
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 255);
}
