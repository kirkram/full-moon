/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/28 14:53:04 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 640
# define SCREENHEIGHT 480

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*instance;
	mlx_image_t		*backg;
	mlx_key_data_t	keydata;
	int32_t			width;
	int32_t			height;
}					t_data;

//helper
int	ft_error(char *msg, int	error_code);

#endif
