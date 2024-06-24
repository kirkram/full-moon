/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/24 15:38:21 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	rad(double angle)
{
	return (angle * PI / 180);
}

void	apply_rotation(t_data *data, t_point *point, int x, int y)
{
	t_player	*player;
	t_point		temp;

	player = data->player;
	temp.x = x * cos(player->angle) - y * sin(player->angle);
	temp.y = x * sin(player->angle) + y * cos(player->angle);
	point->x = temp.x;
	point->y = temp.y;
}

void	draw_minirays(t_data *data, t_ray *ray)
{
	t_point		point;
	t_point		dest;
	t_player	*player;

	player = data->player;
	point.y = player->y_pos_mini;
	point.x = player->x_pos_mini;
	// can add rotation so that the rays will start from the player's centre on the minimap
	if (ray->hor_dist < ray->vert_dist && ray->hor_dist != 0)
	{
		dest.x = ray->x * data->zoom;
		dest.y = ray->y * data->zoom;
		point.color = RED;
	}
	else
	{
		dest.x = ray->x_v * data->zoom;
		dest.y = ray->y_v * data->zoom;
		point.color = GREEN;
	}
	drw_line(point, dest, data, data->player->img);
}

void	fix_fisheye(t_data *data, t_ray *ray)
{
	float	curr_angle;

	curr_angle = data->player->angle - ray->ang;
	if (curr_angle < 0)
		curr_angle += 2 * PI;
	else if (curr_angle >= 2 * PI)
		curr_angle = curr_angle - (2 * PI);
	ray->hor_dist *= cos(curr_angle);
	ray->vert_dist *= cos(curr_angle);
}

void	calc_distance(t_data *data, t_ray *ray)
{
	t_player	*player;

	player = data->player;
	ray->hor_dist = sqrt((ray->x - player->x_pos) * (ray->x - player->x_pos)
			+ (ray->y - player->y_pos) * (ray->y - player->y_pos));
	ray->vert_dist = sqrt((ray->x_v - player->x_pos) * (ray->x_v
				- player->x_pos) + (ray->y_v - player->y_pos) * (ray->y_v
				- player->y_pos));
}

void	vertical_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_map		map;

	player = data->player;
	ray->ntan = -tan(ray->ang);
	ray->dof = 0;
	if ((float)ray->ang == (float)PI_N || (float)ray->ang == (float)PI_S)
	{
		// printf("North or South\n\n\n");
		ray->x_v = player->x_pos;
		ray->y_v = player->y_pos;
		ray->dof = data->map_height;
	}
	else if ((float)ray->ang < (float)PI_N && (float)ray->ang > (float)PI_S)
	{
		ray->x_v = (int)player->x_pos;
		ray->y_v = (player->x_pos - ray->x_v) * ray->ntan + player->y_pos;
		ray->x_off = -1;
		ray->y_off = -ray->x_off * ray->ntan;
	}
	else if (ray->ang > PI_N || ray->ang < PI_S)
	{
		ray->x_v = (int)player->x_pos + 1;
		ray->y_v = (player->x_pos - ray->x_v) * ray->ntan + player->y_pos;
		ray->x_off = 1;
		ray->y_off = -ray->x_off * ray->ntan;
	}
	while (ray->dof < data->map_height)
	{
		map.y = (int)ray->y_v;
		map.x = (int)ray->x_v;
		if ((float)ray->ang < (float)PI_N && (float)ray->ang > (float)PI_S)
			map.x -= 1;
		if (map.x < 0)
			map.x = 0;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width && map.x >= 0
			&& data->world_map[map.y][map.x] == 1)
			ray->dof = data->map_height;
		else
		{
			if (ray->y_v > 0 && ray->y_v < data->map_height)
				ray->y_v += ray->y_off;
			if (ray->x_v > 0 && ray->x_v < data->map_width)
				ray->x_v += ray->x_off;
			ray->dof++;
		}
		if (ray->dof != data->map_height && (ray->y_v < 0 || ray->x_v < 0
				|| ray->x_v >= data->map_width || ray->y_v >= data->map_height))
			break ;
	}
}

void	horizontal_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_map		map;

	player = data->player;
	ray->atan = -1 / tan(ray->ang);
	ray->dof = 0;
	if ((float)ray->ang == (float)0 || (float)ray->ang == (float)PI)
	{
		// printf("0 or PI\n\n\n");
		ray->y = player->y_pos;
		ray->x = player->x_pos;
		ray->dof = data->map_height;
	}
	else if (ray->ang > PI)
	{
		ray->y = (int)(player->y_pos);
		ray->x = (player->y_pos - ray->y) * ray->atan + player->x_pos;
		ray->y_off = -1;
		ray->x_off = -ray->y_off * ray->atan;
	}
	else if (ray->ang < PI)
	{
		ray->y = (int)(player->y_pos) + 1;
		ray->x = (player->y_pos - ray->y) * ray->atan + player->x_pos;
		ray->y_off = 1;
		ray->x_off = -ray->y_off * ray->atan;
	}
	while (ray->dof < data->map_height) 
	{
		map.y = (int)ray->y;
		map.x = (int)ray->x;
		if (ray->ang > PI)
			map.y -= 1;
		if (map.y < 0)
			map.y = 0;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width && map.x >= 0
			&& data->world_map[map.y][map.x] == 1)
			ray->dof = data->map_height;
		else
		{
			if (ray->y > 0 && ray->y < data->map_height)
				ray->y += ray->y_off;
			if (ray->x > 0 && ray->x < data->map_width)
				ray->x += ray->x_off;
			ray->dof++;
		}
		if (ray->dof != data->map_height && (ray->y < 0 || ray->x < 0
				|| ray->x >= data->map_width || ray->y >= data->map_height))
			ray->dof = data->map_height;
	}
}

void	make_color_opaque(unsigned int	*color)
{
	unsigned int	mask;

	mask = 0xFFFFFF00;
	*color = *color & mask;
	mask = 0x000000FF;
	*color = *color | mask;

}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


//ORIGIANL WITH TEXTURE NOT IMAGE

void	draw_column(t_data *data, t_ray *ray, int i)
{
	t_point		line;
	double		dist;
	double		line_w;
	double		line_h;

	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
	uint8_t		alpha;
	uint32_t	index;
	uint8_t		*pixels;

	double		texture_y;
	double		texture_y_step;
	double		texture_x;
	double		texture_x_step;
	double		save;


	pixels = data->texture_1_text->pixels;
	dist = ray->hor_dist;
	texture_y = 0;
	
	texture_x = (double)data->texture_1_text->width * (ray->x - (int)ray->x);
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist
			&& ray->vert_dist != 0))
	{
		dist = ray->vert_dist;
		texture_x = (double)data->texture_1_text->width * (ray->y_v - (int)ray->y_v);
	}
	line_h = data->height / dist;
	line_w = (double)data->width / ((double)(FOV * RESOLUTION));
	line.y = (data->height -line_h) / 2;
	texture_y_step = (double)data->texture_1_text->height / line_h;

	texture_x_step = (double)data->texture_1_text->width / ((double)(FOV * RESOLUTION)) / line_w;
	save = texture_x;
	while (++line.y < (data->height - line_h) / 2 + line_h && line.y < data->height)
	{
		line.x = line_w * i;
		texture_x = save;
		index = (int)texture_y * data->texture_1_text->width + texture_x;
		index *= data->texture_1_text->bytes_per_pixel;
		while (++line.x <= line_w * (i + 1) && line.x < data->width)
		{	
			//less than maxindex, unneecessary?
			// if (index + 2 < (int)data->texture_1_text->width * data->texture_1_text->height 
			// data->texture_1_text->bytes_per_pixel)
			// {
				red = pixels[index];
				green = pixels[index + 1];
				blue = pixels[index + 2];
				alpha = 0x000000FF;
				line.color = get_rgba(red, green, blue, alpha);
			// }
			put_pixel(data, &line, data->screen);
			texture_x += texture_x_step;
		}
		texture_y += texture_y_step;
	}
}

void	draw_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	int			i;

	player = data->player;
	ray->ang = player->angle - DEGR * FOV / 2;
	// dont touch when multiplaying rays
	// printf("Ray->ang float == %f\n\n\n", player->angle * 180 / PI);
	if (ray->ang < 0)
		ray->ang += 2 * PI;
	else if (ray->ang >= 2 * PI)
		ray->ang -= 2 * PI;
	i = -1;
	while (++i < FOV * RESOLUTION)
	{
		horizontal_rays(data, ray);
		vertical_rays(data, ray);
		calc_distance(data, ray);
		fix_fisheye(data, ray);
		//draw_minirays(data, ray);
		draw_column(data, ray, i);
		ray->ang += DEGR_RESO;
		if (ray->ang < 0)
			ray->ang += 2 * PI;
		else if ((float)ray->ang >= (float)2 * PI)
			ray->ang = (float)ray->ang - (float)(2 * PI);
	}
}

int	draw_player(t_data *data)
{
	t_player	*player;
	t_point		point;
	int			x;
	int			y;

	player = data->player;
	y = -1;
	while (++y < PLAYERSIZE)
	{
		x = -1;
		while (++x < PLAYERSIZE)
		{
			point.x = x;
			point.y = y;
			apply_rotation(data, &point, x, y);
			// later may use rounding for more precise results (extra)
			// later may use put_pixel function for less verbosity
			if (player->x_pos_mini + point.x >= 0 && player->y_pos_mini
				+ point.y >= 0 && player->x_pos_mini
				+ point.x < player->imgwidth && player->y_pos_mini
				+ point.y < player->imgheight)
				mlx_put_pixel(player->img, player->x_pos_mini + point.x,
					player->y_pos_mini + point.y, YELLOW);
		}
	}
	return (0);
}

void	put_pixel(t_data *data, t_point *point, mlx_image_t *img)
{
	if (point->x < data->width && point->y < data->height && point->x >= 0
		&& point->y >= 0)
		mlx_put_pixel(img, point->x, point->y, point->color);
	// else
	// 	printf("can't put pixel\n");
}
