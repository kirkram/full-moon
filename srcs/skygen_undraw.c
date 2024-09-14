/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skygen_undraw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 23:17:32 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/14 23:40:08 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static void	undraw_star_n(int x, int y, float brightness, t_data *data)
{
	mlx_put_pixel(data->ceiling, x, y, data->ceilingcolor);
	if (brightness > 0.35)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			undraw_star_n(x, y - 1, brightness / 2, data);
		}
	}
}

static void	undraw_star_s(int x, int y, float brightness, t_data *data)
{
	mlx_put_pixel(data->ceiling, x, y, data->ceilingcolor);
	if (brightness > 0.35)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			undraw_star_s(x, y + 1, brightness / 2, data);
		}
	}
}

static void	undraw_star_e(int x, int y, float brightness, t_data *data)
{
	mlx_put_pixel(data->ceiling, x, y, data->ceilingcolor);
	if (brightness > 0.35)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			undraw_star_e(x + 1, y, brightness / 2, data);
		}
	}
}

static void	undraw_star_w(int x, int y, float brightness, t_data *data)
{
	mlx_put_pixel(data->ceiling, x, y, data->ceilingcolor);
	if (brightness > 0.35)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			undraw_star_w(x - 1, y, brightness / 2, data);
		}
	}
}

void	undraw_star(int x, int y, float brightness, t_data *data) 
{
	// Draw a pixel at (x, y) with the given brightness
	mlx_put_pixel(data->ceiling, x, y, data->ceilingcolor);
	if (brightness > 0.35)
	{
		if (x < (SCREENWIDTH - 1) && x > 0 && y < (SCREENHEIGHT / 2) && y > 0)
		{
			undraw_star_n(x, y -1, brightness / 2, data);
			undraw_star_s(x, y + 1, brightness / 2, data);
			undraw_star_e(x + 1, y, brightness / 2, data);
			undraw_star_w(x - 1, y, brightness / 2, data);
		}
	}
}