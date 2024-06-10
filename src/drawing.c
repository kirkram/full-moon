/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/10 17:39:46 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	vertical_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_map		map;

	player = data->player;
	ray->ntan = -tan(ray->ang);
	ray->dof = 0;
	if ((float)ray->ang == (float)PI_N || (float)ray->ang == (float)PI_S)
	{
		ray->x_v = player->x_pos;
		ray->y_v = player->y_pos;
		ray->dof = MAPHEIGHT;
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
	while (ray->dof < MAPHEIGHT)
	{
		map.y = (int)ray->y_v;
		map.x = (int)ray->x_v;
		if (map.y < MAPHEIGHT && map.y >= 0 && map.x < MAPWIDTH && map.x >= 0 && data->world_map[map.y][map.x] == 1)
			ray->dof = MAPHEIGHT;
		else
		{
			if (ray->y_v > 0 && ray->y_v < MAPHEIGHT)
				ray->y_v += ray->y_off;
			if (ray->x_v > 0 && ray->x_v < MAPWIDTH)
				ray->x_v += ray->x_off;
			ray->dof ++;
		}
		if (ray->dof != MAPHEIGHT && (ray->y_v < 0 || ray->x_v < 0 || ray->x_v >= MAPWIDTH || ray->y_v >= MAPHEIGHT ))
			break;
	}
}

void	horizontal_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_map		map;

	player = data->player;
	ray->atan = -1/tan(ray->ang);
	ray->dof = 0;
	if ((float)ray->ang == (float)0 || (float)ray->ang == (float)PI)
	{
		printf("0 or PI!!\n\n\n");
		ray->y = player->y_pos;
		ray->x = player->x_pos;
		ray->dof = MAPHEIGHT;
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
	while (ray->dof < MAPHEIGHT)
	{
		map.y = (int)ray->y;
		map.x = (int)ray->x;
		if (map.y < MAPHEIGHT && map.y >= 0 && map.x < MAPWIDTH && map.x >= 0 && data->world_map[map.y][map.x] == 1)
			ray->dof = MAPHEIGHT;
		else
		{
			if (ray->y > 0 && ray->y < MAPHEIGHT)
				ray->y += ray->y_off;
			if (ray->x > 0 && ray->x < MAPWIDTH)
				ray->x += ray->x_off;
			ray->dof ++;
		}
		if (ray->dof != MAPHEIGHT && (ray->y < 0 || ray->x < 0 || ray->x >= MAPWIDTH || ray->y >= MAPHEIGHT))
			ray->dof = MAPHEIGHT;
	}
}

void	calc_distance(t_data *data, t_ray *ray)
{
	t_player *player;

	player = data->player;
	ray->hor_dist = sqrt((ray->x - player->x_pos) * (ray->x - player->x_pos) + \
	(ray->y - player->y_pos) * (ray->y - player->y_pos));
	ray->vert_dist = sqrt((ray->x_v - player->x_pos) * (ray->x_v - player->x_pos) + \
	(ray->y_v - player->y_pos) * (ray->y_v - player->y_pos));
}

void	draw_minirays(t_data *data, t_ray *ray)
{
	t_point		point;
	t_point		dest;
	t_player	*player;

	player = data->player;
	point.y = player->y_pos_mini;
	point.x = player->x_pos_mini;

	if (ray->hor_dist < ray->vert_dist)
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
	// if (dest.x > MAPWIDTH * data->zoom)
	// 	dest.x = MAPWIDTH * data->zoom;
	// if (dest.y > MAPHEIGHT * data->zoom)
	// 	dest.y = MAPHEIGHT * data->zoom;
	//printf("dest.x = %d, dest.y = %d\n", dest.x, dest.y);
	drw_line(point, dest, data, data->player->img);
}

void	calc_rays(t_data *data, t_ray *ray)
{
	t_player	*player;

	player = data->player;
	ray->ang = player->angle - DEGR * 30;
	if (ray->ang < 0)
		ray->ang += 2 * PI;
	else if (ray->ang >= 2 * PI)
		ray->ang -= 2 * PI;
	int	i = -1;
	while (++i < FOV)
	{
		//printf("angle = %f, i = %d\n", ray->ang * 180 / PI, i);
		//if (i == 30)
		//	printf("here 30\n");
		horizontal_rays(data, ray);
		vertical_rays(data, ray);
		calc_distance(data, ray); //for now doesnt choose ray just calcs
		draw_minirays(data, ray);
		ray->ang += DEGR;
		if (ray->ang < 0)
			ray->ang += 2 * PI;
		else if ((float)ray->ang >= (float)2 * PI)
			ray->ang = (float)ray->ang - (float)(2 * PI);
	}
}

void	draw_screen(t_data *data)
{
	t_player	*player;
	t_point		line;
	int32_t		linelen;

	player = data->player;
	linelen = (MAPHEIGHT - player->y_pos + 1) * (data->height / 2 / MAPHEIGHT);
	line.y = data->height / 2 - linelen / 2;
	line.color = RED;
	// printf("%d %d\n", line.y, linelen);
	while (++line.y < data->height / 2 + linelen / 2)
	{
		line.x = data->width / 2 - 3; //10 pixels left right
		while (++line.x < data->width / 2 + 3)
		{
			put_pixel(data, &line, data->screen);
		}
	}
	//if we have x-pos - 0 -> draw a line using the length
}

int	draw_player(t_data *data)
{
	t_player	*player;
	t_ray		ray;
	t_point		point;

	player = data->player;
	int		pl_w = 6;
	int		pl_h = 6;
	int		direction_w = pl_w + 10;
	int		direction_h = 3;
	int		x;
	int		y;

	//draw player yellow
	y = -1;
	while (++y < pl_h)
	{
		x = -1;
		while (++x < pl_w)
		{
			point.x = x;
			point.y = y;
			apply_rotation(data, &point, x, y);
			//later may use rounding for more precise results (extra)
			//later may use put_pixel function for less verbosity
			if (player->x_pos_mini + point.x >= 0 && player->y_pos_mini + point.y >= 0 && \
			player->x_pos_mini + point.x < player->imgwidth && player->y_pos_mini + point.y < player->imgheight)
			mlx_put_pixel(player->img, player->x_pos_mini + point.x, \
				player->y_pos_mini + point.y, YELLOW);
		}
	}
	//draw direction red
	y = pl_h / 2 - 2;
	while (++y < direction_h + 1)
	{
		x = pl_w - 1;
		while (++x < direction_w)
		{
			point.x = x;
			point.y = y;
			apply_rotation(data, &point, x, y);
			if (player->x_pos_mini + point.x >= 0 && player->y_pos_mini + point.y >= 0 && \
			player->x_pos_mini + point.x < player->imgwidth && player->y_pos_mini + point.y < player->imgheight)
				mlx_put_pixel(player->img, player->x_pos_mini + point.x, \
				player->y_pos_mini + point.y, RED);
		}
	}
	//draw rays
	data->ray = &ray;
	calc_rays(data, &ray);
	return (0);
}

void	put_pixel(t_data *data, t_point *point, mlx_image_t *img)
{
	if (point->x < data->width && point->y < data->height && \
		point->x >= 0 && point->y >= 0)
		mlx_put_pixel(img, point->x, point->y, point->color);
	// else
	// 	printf("can't put pixel\n");
}
