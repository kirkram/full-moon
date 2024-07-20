/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:11:48 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/19 18:52:43 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_data *data, t_point *point, mlx_image_t *img)
{
	if (point->x < (int32_t)data->width && point->y < (int32_t)data->height && \
	point->x >= 0 && point->y >= 0)
		mlx_put_pixel(img, point->x, point->y, point->color);
}

void	angle_outofbounds_check(t_ray *ray)
{
	if (ray->ang < 0)
		ray->ang += PI2;
	else if (ray->ang >= PI2)
		ray->ang -= PI2;
}

int	is_equal(float a, float b)
{
	return (fabs(a - b) < EPSILON);
}
