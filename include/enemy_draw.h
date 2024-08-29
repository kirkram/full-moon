/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:37:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/08/29 11:21:27 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_DRAW_H
# define ENEMY_DRAW_H

# include "cub3d.h"

typedef struct s_ed
{
	t_point		sc;
	t_point		ds;
	t_point		dst;
	t_point		f;
	mlx_image_t	*dest;
	mlx_image_t	*src;
	int			ray_index;
}	t_ed;

#endif