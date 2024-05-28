/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/05/28 15:58:26 by klukiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 1280
# define SCREENHEIGHT 760
# define MAGENTA 0xFF00FFEE
# define PURPLE 0xB800FFEE
# define WHITE 0xFFFFFFEE
# define YELLOW 0xFFFF00EE
# define YEL_WHITE 0xFFFFB6EE

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*instance;
	mlx_image_t		*backg;
	mlx_key_data_t	keydata;
	int32_t			width;
	int32_t			height;
	int32_t			zoom;
	int				**world_map;
}					t_data;

typedef struct s_point
{
	int				x;
	int				y;
	unsigned int	color;
	void			*content;
}					t_point;

//init
int	copy_example_map(t_data *data);

//drawing
void	draw_minimap(t_data *data);
int		init_and_draw(t_data *data);

//helper
int	ft_error(char *msg, int	error_code);
int	ft_abs(int result);



#endif
