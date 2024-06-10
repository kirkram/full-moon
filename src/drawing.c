/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/10 14:01:01 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	rad(double angle)
{
	return (angle * PI / 180);
}

void	calc_distance(t_data *data, t_ray *ray)
{
	double	hor_dist;
	double	vert_dist;
	t_player *player;

	player = data->player;
	hor_dist = (sqrt((ray->x - player->x_pos)) * (ray->x - player->x_pos) + \
	(ray->y - player->y_pos) * (ray->y - player->y_pos));
	vert_dist = (sqrt((ray->x_v - player->x_pos)) * (ray->x_v - player->x_pos) + \
	(ray->y_v - player->y_pos) * (ray->y_v - player->y_pos));
	if (vert_dist < hor_dist)
		ray->distance = vert_dist;
	else
		ray->distance = hor_dist;
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
	//looking left
	if ((float)ray->ang < (float)PI_N && ray->ang > PI_S)
	{
		printf("vert in < than PI_N\n");
		printf("ray->ang is %f and PI_N is %f\n", ray->ang, PI_N);
		ray->x_v = (int)player->x_pos;
		//длина противолежащего катета *
		ray->y_v = (player->x_pos - ray->x_v) * ray->ntan + player->y_pos;
		//printf("ray y_v is %f\n", ray->y_v);
		ray->x_off = -1;
		ray->y_off = -ray->x_off * ray->ntan;
		//printf("ray  y_off is %f\n", ray->y_off);
	}
	//looking right
	else if (ray->ang > PI_N || ray->ang < PI_S)
	{
		printf("vert in > than PI_N\n");
		ray->x_v = (int)player->x_pos + 1;
		ray->y_v = (player->x_pos - ray->x_v) * ray->ntan + player->y_pos;
		ray->x_off = 1;
		ray->y_off = -ray->x_off * ray->ntan;
	}
	else if (ray->ang == PI_N || ray->ang == PI_S)
	{
		printf("vert in PI_N\n");
		ray->x_v = player->x_pos;
		ray->y_v = player->y_pos;
		ray->dof = MAPHEIGHT;
	}
	else
	{
		ray->x_v = player->x_pos;
		ray->y_v = player->y_pos;
		ray->dof = MAPHEIGHT;
		printf("vert other\n");
	}
	printf("after vert\n");
	//printf("vertical x_off = %f y_off = %f\n", ray->x_off, ray->y_off);
	while (ray->dof < MAPHEIGHT)
	{
		map.y = (int)ray->y_v;
		map.x = (int)ray->x_v;
		//printf("map.y = %d, map.x = %d\n", map.y, map.x);
		if (map.y < MAPHEIGHT && map.y >= 0 && map.x < MAPWIDTH && map.x >= 0 && data->world_map[map.y][map.x] == 1)
			ray->dof = MAPHEIGHT;
		else
		{
			if (ray->y_v > 0 && ray->y_v < SCREENHEIGHT)
				ray->y_v += ray->y_off;
			if (ray->x_v > 0 && ray->x_v < SCREENWIDTH)
				ray->x_v += ray->x_off;
			ray->dof ++;
		}
		if (ray->dof != MAPHEIGHT && (ray->y_v < 0 || ray->x_v < 0 || ray->x_v >= MAPWIDTH || ray->y_v >= MAPHEIGHT))
		{
			// if (ray->y_v < 0 || ray->y_v >= MAPHEIGHT)
			// 	ray->y_v -= ray->y_off;
			// if (ray->x_v < 0 || ray->x_v >= MAPWIDTH)
			// 	ray->x_v -= ray->x_off;
			ray->dof = MAPHEIGHT;
		}
	}
}

void	horizontal_rays(t_data *data, t_ray *ray)
{
	t_player	*player;
	t_map		map;

	player = data->player;
	ray->atan = -1/tan(ray->ang);
	ray->dof = 0;
	if (ray->ang > PI) //we are facing to the beginning of Y, north, up
	{
		//in one of the tutorias its proposed to set the value of ray->y could be rounded to the neartest 64th value
		// there a 8x8 grid each has 64 units of size
		//for me it would be rounding to the nearest int value ?
		//casting to int to get rid of the float remainder
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
	//no rounding problems?
	else if (ray->ang == 0 || ray->ang == PI)
	{
		ray->y = player->y_pos;
		ray->x = player->x_pos;
		ray->dof = MAPHEIGHT;
	}
	// if (ray->y < 0)
	// 	ray->y = 0;
	// if (ray->x < 0)
	// 	ray->x = 0;
	//printf("horizontal x_off = %f y_off = %f\n", ray->x_off, ray->y_off);
	while (ray->dof < MAPHEIGHT)
	{
		map.y = (int)ray->y;
		map.x = (int)ray->x;
		if (map.y < MAPHEIGHT && map.y >= 0 && map.x < MAPWIDTH && map.x >= 0 && data->world_map[map.y][map.x] == 1)
			ray->dof = MAPHEIGHT;
		else
		{
			if (ray->y > 0 && ray->y < SCREENHEIGHT)
				ray->y += ray->y_off;
			if (ray->x > 0 && ray->x < SCREENWIDTH)
				ray->x += ray->x_off;
			ray->dof ++;
		}
		if (ray->dof != MAPHEIGHT && (ray->y < 0 || ray->x < 0 || ray->x >= MAPWIDTH || ray->y >= MAPHEIGHT))
			ray->dof = MAPHEIGHT;
	}
}

void	draw_minirays(t_data *data, t_ray *ray, int i)
{
	t_point		point;
	t_point		dest;
	t_player	*player;

	player = data->player;
	point.x = player->x_pos_mini;
	point.y = player->y_pos_mini;
	point.color = RED;
	if (i == 29 || i == 30)
	{
		printf("here30\n");
	}
	dest.x = ray->x * data->zoom;
	dest.y = ray->y * data->zoom;
	drw_line(point, dest, data, data->player->img);
	point.x = player->x_pos_mini + 2;
	point.y = player->y_pos_mini;
	if (i == 30)
	{
		printf("here30\n");
	}
	dest.x = ray->x_v * data->zoom;
	dest.y = ray->y_v * data->zoom;
	point.color = GREEN;
	drw_line(point, dest, data, data->player->img);

	//printf("Ray y = %f, ray x = %f\n", ray->y, ray->x);
	//printf("Ray y_v = %f, ray x_v = %f\n", ray->y_v, ray->x_v);
}
void	calc_rays(t_data *data, t_ray *ray)
{
	t_player	*player;

	player = data->player;
	ray->ang = player->angle - DEGR * 30;
	if (ray->ang < 0)
		ray->ang += 2 * PI;
	else if (ray->ang > 2 * PI)
		ray->ang -= 2 * PI;
	int	i = -1;
	while (++i < FOV)
	{
		printf("ray angle is %f\n", ray->ang * 180 / PI);
		horizontal_rays(data, ray);
		if (i == 30)
		{
			printf("here after horizontal rays 30 \n");
		}
		vertical_rays(data, ray);
		calc_distance(data, ray); //for now doesnt choose ray just calcs
		draw_minirays(data, ray, i);
		ray->ang += DEGR;
		if (ray->ang < 0)
		{
			ray->ang += 2 * PI;
			printf("ray->ang got less than 0\n");
		}
		else if (ray->ang > 2 * PI)
		{
			ray->ang -= 2 * PI;
			printf("ray->ang got more than 2*PI\n");
		}

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
	printf("%f\n", player->angle);
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
