/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skygen_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:16:13 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/14 23:54:44 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static void	draw_star_n(int x, int y, float brightness, t_data *data)
{
	my_put_pixel(data->ceiling, x, y, get_grayscale_color(brightness));
	if (brightness > 0.4)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			draw_star_n(x, y - 1, brightness / 2, data);
		}
	}
}

static void	draw_star_s(int x, int y, float brightness, t_data *data)
{
	my_put_pixel(data->ceiling, x, y, get_grayscale_color(brightness));
	if (brightness > 0.4)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			draw_star_s(x, y + 1, brightness / 2, data);
		}
	}
}

static void	draw_star_e(int x, int y, float brightness, t_data *data)
{
	my_put_pixel(data->ceiling, x, y, get_grayscale_color(brightness));
	if (brightness > 0.4)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			draw_star_e(x + 1, y, brightness / 2, data);
		}
	}
}

static void	draw_star_w(int x, int y, float brightness, t_data *data)
{
	my_put_pixel(data->ceiling, x, y, get_grayscale_color(brightness));
	if (brightness > 0.4)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			draw_star_w(x - 1, y, brightness / 2, data);
		}
	}
}

void	draw_star(int x, int y, float brightness, t_data *data) 
{
	// Draw a pixel at (x, y) with the given brightness
	my_put_pixel(data->ceiling, x, y, get_grayscale_color(brightness));
	if (brightness > 0.4)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			draw_star_n(x, y -1, brightness / 2, data);
			draw_star_s(x, y + 1, brightness / 2, data);
			draw_star_e(x + 1, y, brightness / 2, data);
			draw_star_w(x - 1, y, brightness / 2, data);
		}
	}
}