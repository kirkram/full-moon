/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/06 12:29:21 by klukiano         ###   ########.fr       */
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
# define MINIZOOM 25
# define STARTPOS 17.5
# define SPEED 0.08

//maths
# define PI 3.14159265359
# define PI_N 3*PI/2
# define PI_S PI/2

//direction angle
# define EAST 0
# define SOUTH 90
# define WEST 180
# define NORTH 270

//colors
# define BLACK 0x000000EE
# define MAGENTA 0xFF00FFEE
# define PURPLE 0xB800FFEE
# define WHITE 0xFFFFFFEE
# define WHITE_ISH 0xFFFFFFAA
# define YELLOW 0xFFFF00EE
# define YEL_WHITE 0xFFFFB6EE
# define RED 0xFF0000EE
# define BLUE 0x0000FFEE
# define GREEN 0x00FF00EE
# define BACKG_COLOR 0x000011FF
# define FULL_TRANSPARENT 0x0000000

typedef struct s_map
{
	int16_t	x;
	int16_t	y;
}	t_map;

typedef struct s_ray
{
	double		x;
	double		y;
	double		x_v;
	double		y_v;
	double		ang;
	double		atan;
	double		ntan;
	double		y_off;
	double		x_off;
	int16_t		dof;
}				t_ray;

typedef struct s_player
{
	mlx_image_t		*img;
	double			x_pos;
	double			y_pos;
	double			x_pos_mini;
	double			y_pos_mini;
	double			angle;
	int32_t			imgwidth;
	int32_t			imgheight;
}					t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*backg;
	t_player		*player;
	t_ray			*ray;
	mlx_key_data_t	keydata;
	int32_t			width;
	int32_t			height;
	int32_t			zoom;
	int				**world_map;
}					t_data;

typedef struct s_point
{
	int32_t				x;
	int32_t				y;
	unsigned int	color;
	void			*content;
}					t_point;

//init
int		copy_example_map(t_data *data);
int		color_whole_image(mlx_image_t *img, int color, int width, int height);

//drawing
void	draw_minimap(t_data *data);
int		init_and_draw(t_data *data);
void	put_pixel(t_data *data, t_point *point, mlx_image_t *img);
int		draw_player(t_data *data);
void	apply_rotation(t_data *data, t_point *point, int x, int y);
double	rad(double angle);
void	draw_screen(t_data *data);
void	drw_line(t_point point, t_point dest, t_data *data, mlx_image_t *img);

//keyhook
void	ft_hook_hub(void *param);
t_data	*reinit_image(t_data *data, mlx_image_t *img);

//helper
int		ft_error(char *msg, int	error_code);
int		ft_abs(int result);
int		free_2d_int(int **int_arr);



#endif
