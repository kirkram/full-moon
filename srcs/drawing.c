/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/10 16:49:32 by klukiano         ###   ########.fr       */
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
	ray->dist *= cosf(curr_angle);
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
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist
			&& ray->vert_dist != 0))
	{
		ray->dist = ray->vert_dist;
		ray->x = ray->x_v;
		ray->y = ray->y_v;
	}
	else
		ray->dist = ray->hor_dist;
}

static int	is_equal(float a, float b)
{
	return (fabs(a - b) < EPSILON);
}

static void	vertical_rays_offset(t_data *data, t_ray *ray, int range)
{
	t_player	*player;

	player = data->player;
	ray->ntan = -tan(ray->ang);
	ray->dof = 0;
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
}

void increment_offset(t_data *data, t_ray *ray, bool is_vert)
{
	if (is_vert)
	{
		if (ray->y_v > 0 && ray->y_v < data->map_height)
			ray->y_v += ray->y_off;
		if (ray->x_v > 0 && ray->x_v < data->map_width)
			ray->x_v += ray->x_off;
	}
	else
	{
		if (ray->y > 0 && ray->y < data->map_height)
			ray->y += ray->y_off;
		if (ray->x > 0 && ray->x < data->map_width)
			ray->x += ray->x_off;
	}
	ray->dof++;
}


int	check_walls(t_data *data, t_ray *ray, t_map *map, bool is_vert)
{
	if (data->world_map[map->y][map->x] == 1)
		return (1);
	if (data->world_map[map->y][map->x] == 4)
	{
		if (is_vert)
			ray->is_doorv = 1;
		else
			ray->is_doorh = 1;
		return (1);
	}
	return (0);
}

void	vertical_rays(t_data *data, t_ray *ray)
{	
	int		range;
	t_map	map;
	
	if (data->map_width > data->map_height)
		range = data->map_width;
	else
		range = data->map_height;
	vertical_rays_offset(data, ray, range);
	while (ray->dof < range)
	{
		map.y = (int)ray->y_v;
		map.x = (int)ray->x_v;
		if (ray->ang > PI_S && ray->ang < PI_N)
			map.x -= 1;
		if (map.x < 0)
			break ;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width
			&& map.x >= 0)
		{
			if (check_walls(data, ray, &map, true))
				break ;
		}
		increment_offset(data, ray, true);
	}
}

static void	horizontal_rays_offset(t_data *data, t_ray *ray, int range)
{
	t_player	*player;

	player = data->player;
	ray->atan = -1 / tanf(ray->ang);
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

}

void	horizontal_rays(t_data *data, t_ray *ray)
{
	t_map		map;
	int			range;
	
	ray->dof = 0;
	range = data->map_height;
	if (data->map_width > data->map_height)
		range = data->map_width;
	horizontal_rays_offset(data, ray, range);
	while (ray->dof < range)
	{
		map.y = (int)ray->y;
		map.x = (int)ray->x;
		if (ray->ang > PI)
			map.y -= 1;
		if (map.y < 0)
			break ;
		if (map.y < data->map_height && map.y >= 0 && map.x < data->map_width
			&& map.x >= 0)
		{
			if (check_walls(data, ray, &map, false))
				break ;
		}
		increment_offset(data, ray, false);
	}
}

uint32_t	index_color(t_txt *txt, t_ray *ray)
{
	txt->red = txt->ptr->pixels[txt->index];
	txt->green = txt->ptr->pixels[txt->index + 1];
	txt->blue = txt->ptr->pixels[txt->index + 2];
	txt->alpha = 0x000000FF;
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist
			&& ray->vert_dist != 0))
	{
		txt->red *= 0.75;
		txt->green *= 0.75;
		txt->blue *= 0.75;
	}
	return (txt->red << 24 | txt->green << 16 | txt->blue << 8 | txt->alpha);
}

static void assign_texture_to_ray(t_data *data, t_ray *ray, t_txt *txt)
{
	
	if (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist && ray->vert_dist != 0))
	{
		if (ray->is_doorv)
			txt->ptr = data->txtrs[4];
		if (ray->ang > PI_S && ray->ang < PI_N)
		{
			if (!ray->is_doorv)
				txt->ptr = data->txtrs[2];
			txt->x = txt->ptr->width * (ray->y - (int)ray->y);
			txt->x = txt->ptr->width - txt->x;
		}
		else
		{
			if (!ray->is_doorv)
				txt->ptr = data->txtrs[3];
			txt->x = txt->ptr->width * (ray->y - (int)ray->y);
		}
	}
	else
	{
		if (ray->is_doorh)
			txt->ptr = data->txtrs[4];
		if (ray->ang < PI)
		{
			if (!ray->is_doorh)
				txt->ptr = data->txtrs[0];
			txt->x = txt->ptr->width * (ray->x - (int)ray->x);
			txt->x = txt->ptr->width - txt->x;
		}
		else
		{
			if (!ray->is_doorh)
				txt->ptr = data->txtrs[1];
			txt->x = txt->ptr->width * (ray->x - (int)ray->x);
		}
	}
}

void	draw_column(t_data *data, t_ray *ray, int i, float line_w)
{
	t_point	line;
	float	line_h;
	t_txt	txt;

	assign_texture_to_ray(data, ray, &txt);
	line_h = data->height / ray->dist * 1.5;
	line.y = (data->height - line_h) / 2;
	txt.y_step = txt.ptr->height / line_h;
	txt.maxindex = txt.ptr->width * txt.ptr->height * txt.ptr->bytes_per_pixel;
	txt.y = 0;
	if (line.y < 0)
	{
		txt.y = fabs(txt.y_step * line.y);
		line.y = 0;
	}
	while (line.y < (data->height - line_h) / 2 + line_h
		&& line.y < (int32_t)data->height)
	{
		line.x = line_w * i;
		txt.index = ((uint32_t)txt.y * txt.ptr->width + (uint32_t)txt.x)
			* txt.ptr->bytes_per_pixel;
		if (txt.index + 2 < txt.maxindex)
			line.color = index_color(&txt, ray);
		while (++line.x <= line_w * (i + 1) && line.x < (int32_t)data->width)
			put_pixel(data, &line, data->screen);
		line.y ++;
		txt.y += txt.y_step;
	}
}

void	angle_outofbounds_check(t_ray *ray)
{
	if (ray->ang < 0)
		ray->ang += PI2;
	else if (ray->ang >= PI2)
		ray->ang -= PI2;
}

int	draw_rays(t_data *data)
{
	t_player	*player;
	t_ray		*ray;
	int			i;

	player = data->player;
	ray = data->ray;
	ray->ang = player->angle - rad(FOV / 2); //(DEGR * FOV) / 2;
	angle_outofbounds_check(ray);
	i = -1;
	while (++i < FOV * RESOLUTION)
	{
		ray->is_doorh = 0;
		ray->is_doorv = 0;
		horizontal_rays(data, ray);
		vertical_rays(data, ray);
		calc_distance(data, ray);
		fix_fisheye(data, ray);
		draw_minirays(data, ray);
		draw_column(data, ray, i, data->width / ((float)(FOV * RESOLUTION)));
		data->raydis[i] = ray->dist;
		ray->ang += DEGR_RESO;
		angle_outofbounds_check(ray);
	}
	return (0);
}

void	draw_sprites(t_data *data)
{
	(void)data;
	return ;
}

int	draw_player_minimap(t_data *data)
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
	if (point->x < (int32_t)data->width && point->y < (int32_t)data->height && \
	point->x >= 0 && point->y >= 0)
		mlx_put_pixel(img, point->x, point->y, point->color);
}
