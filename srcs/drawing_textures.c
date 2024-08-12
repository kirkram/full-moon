/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:17:29 by klukiano          #+#    #+#             */
/*   Updated: 2024/08/12 17:17:52 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


uint32_t	index_color_floor(t_txt *txt, t_ray *ray, float dist_from_middle, t_data *data)
{
	txt->red = txt->ptr->pixels[txt->index];
	txt->green = txt->ptr->pixels[txt->index + 1];
	txt->blue = txt->ptr->pixels[txt->index + 2];
	txt->alpha = 0x000000FF;

	(void) data;
	float darken_factor = 1.0f / (dist_from_middle * 1.9f);
	(void) ray;
	// if (darken_factor > 1.0f) 
	// 	darken_factor = 1.0f;

	if (darken_factor > 0.6f) 
		darken_factor = 0.6f;
    // if (darken_factor < 0.1f) 
	// 	darken_factor = 0.1f; // Prevents it from getting too dark

    txt->red *= darken_factor;
    txt->green *= darken_factor;
    txt->blue *= darken_factor;
	
	return (txt->red << 24 | txt->green << 16 | txt->blue << 8 | txt->alpha);
}

uint32_t	index_color(t_txt *txt, t_ray *ray, bool is_wall)
{
	txt->red = txt->ptr->pixels[txt->index];
	txt->green = txt->ptr->pixels[txt->index + 1];
	txt->blue = txt->ptr->pixels[txt->index + 2];
	txt->alpha = 0x000000FF;

	float darken_factor = 1.0f / (ray->dist * 0.5f);
	// if (darken_factor > 1.0f) 
	// 	darken_factor = 1.0f;

	if (darken_factor > 0.6f) 
		darken_factor = 0.6f;
    // if (darken_factor < 0.1f) 
	// 	darken_factor = 0.1f; // Prevents it from getting too dark

	// if (is_wall && (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist
	// 		&& ray->vert_dist != 0)))
	// {
	// if (is_wall)
	// {
	// 	txt->red *= darken_factor;
	// 	txt->green *= darken_factor;
	// 	txt->blue *= darken_factor;
	// }
	// if (!is_wall)
	// {
	// 	txt->red *= 0.75;
	// 	txt->green *= 0.75;
	// 	txt->blue *= 0.75;
	// }

	// Apply darkening based on wall or not
    if (is_wall && (ray->hor_dist == 0 || (ray->hor_dist > ray->vert_dist && ray->vert_dist != 0)))
    {
        darken_factor *= 0.65f;
    }
    else if (!is_wall)
    {
        darken_factor *= 0.75f;
    }

    // Apply the darkening factor to the color components
    txt->red *= darken_factor;
    txt->green *= darken_factor;
    txt->blue *= darken_factor;
	
	return (txt->red << 24 | txt->green << 16 | txt->blue << 8 | txt->alpha);
}

static void	assign_texture_to_ray_hor(t_data *data, t_ray *ray, t_txt *txt)
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

static void	assign_texture_to_ray_vert(t_data *data, t_ray *ray, t_txt *txt)
{
	if (ray->is_doorv)
		txt->ptr = data->txtrs[4];
	if (ray->ang > PI_S && ray->ang < PI_N)
	{
		if (!ray->is_doorv)
			txt->ptr = data->txtrs[2];
		txt->x = txt->ptr->width - (txt->ptr->width * (ray->y - (int)ray->y));
	}
	else
	{
		if (!ray->is_doorv)
			txt->ptr = data->txtrs[3];
		txt->x = txt->ptr->width * (ray->y - (int)ray->y);
	}
}

void	assign_texture_to_ray(t_data *data, t_ray *ray, t_txt *txt)
{
	if (ray->hor_dist == 0 || \
	(ray->hor_dist > ray->vert_dist && ray->vert_dist != 0))
		assign_texture_to_ray_vert(data, ray, txt);
	else
		assign_texture_to_ray_hor(data, ray, txt);
}
