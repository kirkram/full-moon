/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skygen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:49:29 by mburakow          #+#    #+#             */
/*   Updated: 2024/09/14 23:43:39 by mburakow         ###   ########.fr       */
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
        data->stars[i].brightness = ((float) rand() / RAND_MAX); // Random brightness
		data->stars[i].timer = ((float) rand() / RAND_MAX) + 1; // Random timer
		i++;
	}
}

uint32_t get_grayscale_color(float brightness)
{
    uint8_t grayscale;

    // Clamp brightness to the range [0.0, 1.0] to avoid overflows
    if (brightness < 0.0f) brightness = 0.0f;
    if (brightness > 1.0f) brightness = 1.0f;

    // Scale brightness to the range [0, 255]
    grayscale = (uint8_t)(brightness * 255);

    // Return the grayscale color in the format 0xRRGGBBAA
    return (grayscale << 24 | grayscale << 16 | grayscale << 8 | 0xFF); // Alpha is set to full opacity (0xFF)
}

/*
static void unrender_stars(t_data *data) 
{
	int i;

	i = 0;
	while (i < NUM_STARS) 
	{
        // Adjust star's angle based on player's angle
        float relative_angle = data->stars[i].angle - data->player->prev_angle;
        if (relative_angle < 0) relative_angle += PI2; // Ensure angle wraps around

        // Convert angle to screen x-coordinate (cylindrical mapping)
        int x = (relative_angle / PI2) * SCREENWIDTH;
        int y = (int)data->stars[i].height;

        // Render the star at (x, y) on the screen
		undraw_star(x, y, data->stars[i].brightness, data); // Replace with your rendering function
		i++;
    }
}
*/

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
	float	random;

	i = 0;
	//printf("Rendering stars\n");
	//color_whole_image(data->ceiling, data->ceilingcolor, data->width,
	//	data->height / 2);
	// Clear the screen
	if (data->player->prev_angle != data->player->angle)
	{
		color_differing_pixels(data->ceiling, data->width, data->height / 2, data);
		//unrender_stars(data);
		//color_differing_pixels(data->ceiling, data->width, data->height / 2, data);
	}
	// Render each star
	now = mlx_get_time();
	random = ((float) rand() / RAND_MAX);
	factor = SCREENWIDTH / PI2;
	while (i < NUM_STARS) 
	{
		if (now - data->stars[i].timer > (rand() / 10000))
		{
			data->stars[i].brightness += (random - 0.5) / 2;
			if (data->stars[i].brightness > 1.6)
				data->stars[i].brightness -= random * 2;
			else if (data->stars[i].brightness < 0.4)
				data->stars[i].brightness += random * 2;
			data->stars[i].timer = now + random;
		}
        // Adjust star's angle based on player's angle
        float relative_angle = data->stars[i].angle - data->player->angle;
        if (relative_angle < 0) 
			relative_angle += PI2; // Ensure angle wraps around

        // Convert angle to screen x-coordinate (cylindrical mapping)
        x = (int)(relative_angle * factor);

        // Render the star at (x, y) on the screen
        draw_star(x, data->stars[i].height, data->stars[i].brightness, data); // Replace with your rendering function
		i++;
    }
	data->player->prev_angle = data->player->angle;
}
