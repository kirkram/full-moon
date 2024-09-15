/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skygen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:49:29 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/15 20:54:32 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void generate_stars(t_data *data) 
{
	int 			i;

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
	data->moon_angle = ((float) rand() / RAND_MAX) * PI2;
	data->moon_txt = mlx_load_png(MOON_PATH);
	if (!data->moon_txt)
		free_all_and_quit(data, "Error\nMoon texture couldn't load", 79);
	data->moon = mlx_new_image(data->mlx, data->moon_txt->width, data->moon_txt->height);
	if (!data->moon)
		free_all_and_quit(data, "Error\nMoon mlx_new_image", 11);
	data->moon = mlx_texture_to_image(data->mlx, data->moon_txt);
	data->moon_yposneg = (int)((((float) rand() / RAND_MAX) * SCREENHEIGHT / 4) + data->moon_txt->height / 2);
}

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

void copy_image_to_image(mlx_image_t *dest, mlx_image_t *src, int dx, int dy) 
{
    int src_width = src->width;
    int src_height = src->height;
    int dest_width = dest->width;
    int dest_height = dest->height;

    for (int y = 0; y < src_height; y++) {
        for (int x = 0; x < src_width; x++) {
            int src_index = (y * src_width + x) * 4;
			if (src->pixels[src_index + 3] == 0) 
				continue;
            int dest_index = ((dy + y) * dest_width + (dx + x)) * 4;
            if (dx + x >= 0 && dx + x < dest_width && dy + y >= 0 && dy + y < dest_height) 
			{
                dest->pixels[dest_index + 0] = src->pixels[src_index + 0];
                dest->pixels[dest_index + 1] = src->pixels[src_index + 1];
                dest->pixels[dest_index + 2] = src->pixels[src_index + 2];
                dest->pixels[dest_index + 3] = src->pixels[src_index + 3];
            }
        }
    }
}

void render_moon(t_data *data)
{
	float	relative_angle;

	if (!is_equal(data->player->prev_angle, data->player->angle))
	{
		relative_angle = normalize_rad(data->moon_angle - data->player->angle);
		relative_angle *= PARALLAX_MULT;
		relative_angle = normalize_rad(relative_angle);
		data->moon_xpos = (int)(relative_angle * SCREENWIDTH / PI2);
		if (data->moon_xpos <= SCREENWIDTH - (int)(data->moon->width / 2)  && data->moon_xpos >= (int)data->moon->width / 2)
		copy_image_to_image(data->ceiling, data->moon, data->moon_xpos, data->moon_yposneg);
	}
}

void render_stars(t_data *data) 
{
	int 	i;
	float	factor;
	double	now;
	int16_t	random;
	float 	relative_angle;

	i = 0;
	if (!is_equal(data->player->prev_angle, data->player->angle))
		color_differing_pixels(data->ceiling, data->width, data->height / 2, data);
	now = mlx_get_time();
	random = rand() % 255;
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
		relative_angle = normalize_rad(data->stars[i].angle - data->player->angle);
		relative_angle *= PARALLAX_MULT;
		relative_angle = normalize_rad(relative_angle);
        draw_star((int)(relative_angle * factor), data->stars[i].height, &data->stars[i], data);
		i++;
    }
}
