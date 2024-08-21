/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:37:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/21 12:37:56 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_ed
{
	t_point sc;        // point from source
	t_point ds;        // point from destination
	t_point dst;       // coordinates where to draw
	t_point f;         // target pixel
	mlx_image_t *dest; // destination image
	mlx_image_t *src;  // source image (current sprite)
	int ray_index;     // index of ray that gets checked for z
}			t_ed;