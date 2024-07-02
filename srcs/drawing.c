/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/02 14:58:13 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	apply_rotation(t_data *data, t_point *point, int x, int y)
{
	t_player	*player;
	t_point		temp;

	player = data->player;
	temp.x = x * cosf(player->angle) - y * sinf(player->angle);
	temp.y = x * sinf(player->angle) + y * cosf(player->angle);
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
		curr_angle += PI2;
	else if (curr_angle >= PI2)
		curr_angle = curr_angle - (PI2);
	ray->hor_dist *= cosf(curr_angle);
	ray->vert_dist *= cosf(curr_angle);
	// printf("curr ang is %f, distance is %f ", curr_angle * 180 / PI, ray->dist);
	// ray->dist *= cosf(curr_angle);
	// printf("and with correction its %f\n", ray->dist);
	// sleep(1);
}

void	calc_distance(t_data *data, t_ray *ray)
{
	t_player	*player;

	player = data->player;
	ray->hor_dist = sqrtf((ray->x - player->x_pos) * (ray->x - player->x_pos)
			+ (ray->y - player->y_pos) * (ray->y - player->y_pos));
	ray->vert_dist = sqrtf((ray->x_v - player->x_pos) * (ray->x_v
				- player->x_pos) + (ray->y_v - player->y_pos) * (ray->y_v
				- player->y_pos));
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist && ray->vert_dist != 0))
		ray->dist = ray->vert_dist;
	else
		ray->dist = ray->hor_dist;
}

static int is_equal(float a, float b) {
	return (fabs(a - b) < EPSILON);
}

void	vertical_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_map		map;


	player = data->player;
	ray->ntan = -tan(ray->ang);
	ray->dof = 0;
	int range = data->map_height;
	if (data->map_width > data->map_height)
		range = data->map_width;
	if (is_equal(ray->ang, PI_N) || is_equal(ray->ang, PI_S))
	{
		ray->x_v = player->x_pos;
		ray->y_v = player->y_pos;
		ray->dof = range;
	}
	else if (ray->ang < PI_N && ray->ang > PI_S)
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
	while (ray->dof < range)
	{
		map.y = (int)ray->y_v;
		map.x = (int)ray->x_v;
		if (ray->ang > PI_S && ray->ang < PI_N)
			map.x -= 1;
		if (map.x < 0)
			break ;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width && map.x >= 0 
			&& (data->world_map[map.y][map.x] == 1 || data->world_map[map.y][map.x] == 4))
			break; 
		else
		{
			if (ray->y_v > 0 && ray->y_v < data->map_height)
				ray->y_v += ray->y_off;
			if (ray->x_v > 0 && ray->x_v < data->map_width)
				ray->x_v += ray->x_off;
			ray->dof++;
		}
		if (ray->y_v < 0 || ray->x_v < 0
				|| ray->x_v >= data->map_width || ray->y_v >= data->map_height)
			break ;
	}
}

void	horizontal_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_map		map;

	player = data->player;
	ray->atan = -1 / tanf(ray->ang);
	ray->dof = 0;
	int range = data->map_height;
	if (data->map_width > data->map_height)
		range = data->map_width;
	/*
	error: floating-point comparison is always false; 
	constant cannot be represented exactly in type 'float'
	because how they are represented as bits.
	this is why some maps failed to show EW textures.
	*/
	//unsigned long start = current_time();
	if (is_equal(ray->ang, 0.0) || is_equal(ray->ang, PI))
	{
		ray->y = player->y_pos;
		ray->x = player->x_pos;
		ray->dof = range;
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
	while (ray->dof < range) 
	{
		map.y = (int)ray->y;
		map.x = (int)ray->x;
		if (ray->ang > PI)
			map.y -= 1;
		if (map.y < 0)
			break ;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width && map.x >= 0
			&& (data->world_map[map.y][map.x] == 1 || data->world_map[map.y][map.x] == 4))
			break ;
		else
		{
			if (ray->y > 0 && ray->y < data->map_height)
				ray->y += ray->y_off;
			if (ray->x > 0 && ray->x < data->map_width)
				ray->x += ray->x_off;
			ray->dof++;
		}
		if (ray->y < 0 || ray->x < 0
				|| ray->x >= data->map_width || ray->y >= data->map_height)
			break ;
	}
	//printf("Drew a hor ray in %lu\n", current_time() - start);
}

void	make_color_opaque(unsigned int	*color)
{
	unsigned int	mask;

	mask = 0xFFFFFF00;
	*color = *color & mask;
	mask = 0x000000FF;
	*color = *color | mask;
}

uint32_t	index_color(t_txt *txt, t_ray *ray)
{
	txt->red = txt->ptr->pixels[txt->index];
	txt->green = txt->ptr->pixels[txt->index + 1];
	txt->blue = txt->ptr->pixels[txt->index + 2];
	txt->alpha = 0x000000FF;
	//shade if a vertical ray
	//(void)ray;
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist && ray->vert_dist != 0))
	{
		txt->red *= 0.75;
		txt->green *= 0.75;
		txt->blue *= 0.75;
	}
	return (txt->red << 24 | txt->green  << 16 | txt->blue << 8 | txt->alpha);
}

//Old drawinng
// int	draw_column(t_data *data, t_ray *ray, int i)
// {
// 	t_point		line;
// 	double		dist;
// 	double		line_w;
// 	dist = ray->hor_dist;
// 	line.color = YEL_WHITE;
// 	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist && ray->vert_dist != 0))
// 	{
// 		dist = ray->vert_dist;
// 		line.color = YEL_WHITE_SHADE;
// 	}
// 	//will this cast work in every compiler?
// 	line_w = (double)SCREENWIDTH / (FOV * RESOLUTION);
// 	line.y = data->height / 2 - 1;
// 	while (++line.y < (data->height / 2) + SCREENHEIGHT / dist / 2 && line.y < SCREENHEIGHT)
// 	{
// 		//error accumulates with the truncating of the line_w
// 		line.x = line_w * i;
// 		while (++line.x <= line_w * (i + 1) && line.x < SCREENWIDTH)
// 			put_pixel(data, &line, data->screen);
// 	}
// 	line.y = data->height / 2;
// 	while (--line.y > (data->height / 2) - SCREENHEIGHT / dist / 2 && line.y >= 0)
// 	{
// 		line.x = line_w * i;
// 		while (++line.x <= line_w * (i + 1))
// 			put_pixel(data, &line, data->screen);
// 	}
// 	return (0);
// }

int		draw_column(t_data *data, t_ray *ray, int i, float line_w)
{
	t_point		line;
	float		dist;
	float		line_h;
	t_txt		txt;

	//unsigned long start = current_time();
	
	dist = ray->hor_dist;
	txt.y = 0;
	//north is 0, s 1, e 2, w 3
	txt.ptr = data->txtrs[1];
	txt.x = txt.ptr->width * (ray->x - (int)ray->x);
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist && ray->vert_dist != 0))
	{
		dist = ray->vert_dist;
		ray->x = ray->x_v;
		ray->y = ray->y_v;
		//ray->hor_dist = ray->vert_dist;
		//if wall faces west, flip
		if (ray->ang > PI_S && ray->ang < PI_N)
		{
			txt.ptr = data->txtrs[2];
			txt.x = txt.ptr->width * (ray->y_v - (int)ray->y_v);
			txt.x = txt.ptr->width - txt.x;
		}
		else
		{
			txt.ptr = data->txtrs[3];
			txt.x = txt.ptr->width * (ray->y_v - (int)ray->y_v);
		}	
	}
	else
	{
		//face north, flip
		if (ray->ang < PI)
		{
			txt.ptr = data->txtrs[0];
			txt.x = txt.ptr->width * (ray->x - (int)ray->x);
			txt.x = txt.ptr->width - txt.x;
		}
			
	}
	line_h = data->height / dist * 1.5;
	// line.y = (data->height - line_h) / 2;
	line.y = (data->height - line_h) / 2;
	txt.y_step = txt.ptr->height / line_h;
	//txt.x_step = txt.ptr->width / ((FOV * RESOLUTION)) / line_w;
	txt.maxindex = txt.ptr->width * txt.ptr->height * txt.ptr->bytes_per_pixel;
	if (line.y < 0)
	{
		txt.y = fabs(txt.y_step * line.y);
		line.y = 0;
	}
	while (line.y < (data->height - line_h) / 2 + line_h && line.y < data->height)
	{
		line.x = line_w * i;
		txt.index = ((uint32_t)txt.y * txt.ptr->width + (uint32_t)txt.x) * txt.ptr->bytes_per_pixel;
		if (txt.index + 2 < txt.maxindex)
			line.color = index_color(&txt, ray);
		while (++line.x <= line_w * (i + 1) && line.x < data->width)
			put_pixel(data, &line, data->screen);
		line.y ++;
		txt.y += txt.y_step;
	}
	// line.y is the start position for the floor
	// while (line.y < data->height)
	// {
	// 	line.y ++;
	// }
	// int	player_height = data->height / data->zoom;


	return (0);
}

// int	draw_floor(t_data *data, t_ray *ray, int i)
// {


// 	return (0);
// }

int	draw_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	int			i;
	float		line_w;

	player = data->player;
	ray->ang = player->angle - (DEGR * FOV) / 2;
	if (ray->ang < 0)
		ray->ang += PI2;
	else if (ray->ang >= PI2)
		ray->ang -= PI2;
	line_w = data->width / ((float)(FOV * RESOLUTION));
	i = -1;
	while (++i < FOV * RESOLUTION)
	{
		horizontal_rays(data, ray);
		vertical_rays(data, ray);
		calc_distance(data, ray);
		fix_fisheye(data, ray);
		//draw_minirays(data, ray);
		if (draw_column(data, ray, i, line_w))
			return (1);
		ray->ang += DEGR_RESO;
		if (ray->ang < 0)
			ray->ang += PI2;
		else if (ray->ang >= PI2)
			ray->ang = ray->ang - (PI2);
	}
	return (0);
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
}
