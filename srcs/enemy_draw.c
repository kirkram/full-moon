/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:42:11 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/22 12:01:52 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "enemy_draw.h"

static void	initialize_draw_data(t_ed *d, t_enemy *enemy, t_coord dst,
	t_data *data)
{
	d->dest = data->screen;
	d->src = data->enemy_frame[enemy->current_frame];
	d->sc.x = -1;
	d->sc.y = -1;
	d->dst.x = dst.x;
	d->dst.y = dst.y;
}

static void	draw_scaled_pixel_block(t_ed *d, t_enemy *enemy)
{
	d->ds.y = -1;
	while (++d->ds.y < enemy->scale)
	{
		d->ds.x = -1;
		while (++d->ds.x < enemy->scale)
		{
			d->f.x = d->dst.x + d->sc.x * enemy->scale + d->ds.x;
			d->f.y = d->dst.y + d->sc.y * enemy->scale + d->ds.y;
			if ((uint32_t)d->f.x < d->dest->width
				&& (uint32_t)d->f.y < d->dest->height)
				mlx_put_pixel(d->dest, d->f.x, d->f.y, d->sc.color);
		}
	}
}

static void	draw_sprite_column(t_ed *d, t_enemy *enemy)
{
	while (++(d->sc.y) < (int32_t)d->src->height)
	{
		d->sc.color = get_pixel_color(d->src, (uint32_t)d->sc.x,
				(uint32_t)d->sc.y);
		if (get_a(d->sc.color) > 0)
		{
			draw_scaled_pixel_block(d, enemy);
		}
	}
	d->sc.y = -1;
}

void	draw_enemy_onto_canvas(t_enemy *enemy, int dest_x, int dest_y,
		t_data *data)
{
	t_ed	d;
	t_coord	dst;

	dst.x = dest_x;
	dst.y = dest_y;
	initialize_draw_data(&d, enemy, dst, data);
	while (++(d.sc.x) < (int32_t)d.src->width)
	{
		d.ray_index = (d.dst.x + d.sc.x * enemy->scale) * (FOV * RESOLUTION)
			/ data->width;
		if (d.ray_index >= 180)
			d.ray_index = 179;
		if (data->raydis[d.ray_index] > enemy->distance)
		{
			draw_sprite_column(&d, enemy);
		}
	}
}

/*
void	draw_enemy_onto_canvas(t_enemy *enemy, int dest_x, int dest_y,
		t_data *data)
{
	t_ed	d;

	d.dest = data->screen;
	d.src = data->enemy_frame[enemy->current_frame];
	d.sc.y = -1;
	d.sc.x = -1;
	d.dst.x = dest_x;
	d.dst.y = dest_y;
	while (++(d.sc.x) < (int32_t)d.src->width)
	{
		d.ray_index = (d.dst.x + d.sc.x * enemy->scale) * (FOV * RESOLUTION)
			/ data->width;
		if (d.ray_index >= 180)
			d.ray_index = 179;
		if (data->raydis[d.ray_index] > enemy->distance)
		{
			while (++(d.sc.y) < (int32_t)d.src->height)
			{
				d.sc.color = get_pixel_color(d.src, (uint32_t)d.sc.x,
						(uint32_t)d.sc.y);
				if (get_a(d.sc.color) > 0)
				{
					d.ds.y = -1;
					while (++d.ds.y < enemy->scale)
					{
						d.ds.x = -1;
						while (++d.ds.x < enemy->scale)
						{
							d.f.x = dest_x + d.sc.x * enemy->scale + d.ds.x;
							d.f.y = dest_y + d.sc.y * enemy->scale + d.ds.y;
							if ((uint32_t)d.f.x < d.dest->width
								&& (uint32_t)d.f.y < d.dest->height)
							{
								mlx_put_pixel(d.dest, d.f.x, d.f.y, d.sc.color);
							}
						}
					}
				}
			}
		}
		d.sc.y = -1;
	}
}
*/