/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skygen_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:16:13 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/15 02:05:20 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	draw_star(int x, int y, t_star *star, t_data *data) 
{
	int 		i;
	uint32_t	color;
	uint16_t	brightness;

	i = 0;
	brightness = star->brightness;
	mlx_put_pixel(data->ceiling, x, y, get_star_color(brightness, star));
	if (brightness > 150)
	{
		while (i < 4 && brightness > 40)
		{
			brightness /= 2;
			color = get_star_color(brightness, star);
			i++;
			if (x < (SCREENWIDTH - i))
				mlx_put_pixel(data->ceiling, x + i, y, color);
			if (x > i)
				mlx_put_pixel(data->ceiling, x - i, y, color);
			if (y < (SCREENHEIGHT / 2 - i))
				mlx_put_pixel(data->ceiling, x, y + i, color);
			if (y > i)
				mlx_put_pixel(data->ceiling, x, y - i, color);
		}
	}
}