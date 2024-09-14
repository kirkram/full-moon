/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skygen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:49:29 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/15 02:04:04 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void generate_stars(t_data *data) 
{
	int i;

	i = 0;
    while (i < NUM_STARS) 
	{
        data->stars[i].angle = ((float) rand() / RAND_MAX) * PI2; // Random angle (0 to 2*PI)
        data->stars[i].height = (int)(((float) rand() / RAND_MAX) * SCREENHEIGHT / 2); // Random height (top half of screen)
        data->stars[i].brightness = rand() % 400; // Random brightness
		data->stars[i].timer = mlx_get_time();
		data->stars[i].blinkspeed = ((double) rand() / RAND_MAX) + 0.5;
		data->stars[i].red = (uint8_t)(rand() % 20 + 235);
		data->stars[i].green = (uint8_t)(rand() % 20 + 235);
		data->stars[i].blue = (uint8_t)(rand() % 20 + 235);
		i++;
	}
}

/*
uint32_t get_grayscale_color(float brightness)
{
    uint8_t grayscale;

    if (brightness < 0.0f) brightness = 0.0f;
    if (brightness > 1.0f) brightness = 1.0f;
    grayscale = (uint8_t)(brightness * 255);
    return (grayscale << 24 | grayscale << 16 | grayscale << 8 | 0xFF);
}
*/

uint32_t get_star_color(uint16_t brightness, t_star *star) 
{
    uint32_t red;
	uint32_t green;
	uint32_t blue;

    if (brightness > 255) brightness = 255;
	red = brightness * star->red / 255;
	green = brightness * star->green / 255;
	blue = brightness * star->blue / 255;
	if (red > 255) red = 255;
	if (green > 255) green = 255;
	if (blue > 255) blue = 255;
    return (red << 24 | green << 16 | blue << 8 | 0xFF);
}

static void	color_differing_pixels(mlx_image_t *img, int width, int height, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (get_pixel_color(img, x, y) != data->ceilingcolor)
			{
				mlx_put_pixel(img, x, y, data->ceilingcolor);
			}
			x++;
		}
		y++;
	}
}

void render_stars(t_data *data) 
{
	int 	i;
	int		x;
	float	factor;
	double	now;
	int16_t	random;

	i = 0;
	if (data->player->prev_angle != data->player->angle)
		color_differing_pixels(data->ceiling, data->width, data->height / 2, data);
	now = mlx_get_time();
	random = rand() % 255;
	//printf("random: %d\n", random);
	factor = SCREENWIDTH / PI2;
	while (i < NUM_STARS) 
	{
		if (now - data->stars[i].timer > data->stars[i].blinkspeed)
		{
			if (data->stars[i].brightness > 192)
				data->stars[i].brightness -= random / 4;
			else if (data->stars[i].brightness < 64)
				data->stars[i].brightness += random / 4;
			else
				data->stars[i].brightness += (random - 127) / 4;
			data->stars[i].timer = now + (random / 100);
		}
        float relative_angle = data->stars[i].angle - data->player->angle;
        if (relative_angle < 0) 
			relative_angle += PI2;
        x = (int)(relative_angle * factor);
        draw_star(x, data->stars[i].height, &data->stars[i], data); // Replace with your rendering function
		i++;
    }
	data->player->prev_angle = data->player->angle;
}
