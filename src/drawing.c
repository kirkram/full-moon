/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:00:06 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/05 17:00:20 by klukiano         ###   ########.fr       */
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
	temp.y = y * cos(player->angle) + x * sin(player->angle);
	point->x = temp.x;
	point->y = temp.y;
}
void	calc_rays(t_data *data, t_ray *ray)
{
	//draw 1 ray
	double 		atan;
	double		y_off;
	double		x_off;
	int16_t		dof;
	t_map		map;
	t_player	*player;

	player = data->player;
	ray->ang = player->angle;
	dof = 0;
	atan = -1/tan(ray->ang);
	//HORIZONTAL
	if (ray->ang > PI) //we are facing to the beginning of Y, north, up
	{
		//in one of the tutorias its proposed to set the value of ray->y could be rounded to the neartest 64th value
		// there a 8x8 grid each has 64 units of size
		//for me it would be rounding to the nearest int value ?
		//casting to int to get rid of the float remainder
		ray->y = (int)(player->y_pos);
		ray->x = (player->y_pos - ray->y) * atan + player->x_pos;
		y_off = -1;
		x_off = -y_off * atan;
	}
	else if (ray->ang < PI)
	{
		ray->y = (int)(player->y_pos) + 1;
		ray->x = (player->y_pos - ray->y) * atan + player->x_pos;
		y_off = 1;
		x_off = -y_off * atan;
	}
	//no rounding problems?
	else if (ray->ang == 0 || ray->ang == PI)
	{
		ray->y = player->y_pos;
		ray->x = player->x_pos;
		dof = MAPHEIGHT;
	}
	if (ray->y < 0)
		ray->y = 0;
	if (ray->x < 0)
		ray->x = 0;
	while (dof < MAPHEIGHT / 2)
	{
		map.y = (int)ray->y;
		map.x = (int)ray->x;
		if (map.y < MAPHEIGHT && map.x < MAPWIDTH && data->world_map[map.y][map.x] == 1)
			dof = MAPHEIGHT;
		else
		{
			ray->y += y_off;
			ray->x += x_off;
			if (ray->y < 0)
				ray->y = 0;
			if (ray->x < 0)
				ray->x = 0;
			dof ++;
		}
	}
	printf("Ray y = %f, ray x = %f\n", ray->y, ray->x);
}

void	draw_screen(t_data *data)
{
	t_player *player;
	t_point		line;
	int32_t	linelen;

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
	t_point		point;
	t_point		dest;
	t_ray		ray;

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
	calc_rays(data, &ray);
	point.x = player->x_pos_mini;
	point.y = player->y_pos_mini;
	point.color = RED;
	dest.x = ray.x * data->zoom;
	dest.y = ray.y * data->zoom;
	drw_line(point, dest, data, data->player->img);
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
