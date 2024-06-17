/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/17 11:23:50 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define MAPWIDTH 24
# define MAPHEIGHT 24
// for future editions and now (dynamic mapsizes)
# define MAX_MAPWIDTH 24
# define MAX_MAPHEIGHT 24
# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define MINIZOOM SCREENWIDTH / 120
# define PLAYERSIZE MINIZOOM / 2
# define STARTPOS 1.2
# define RESOLUTION 5

# define DEGR 0.0174533
# define DEGR_RESO 0.0174533 / RESOLUTION
# define FOV 60

//maths
# define PI 3.14159265359
# define PI_N 4.71238898039
# define PI_S PI / 2

//direction angle
# define EAST 0
# define SOUTH 90
# define WEST 180
# define NORTH 270

//TEMP TEMP TEMP TEMP TEMP
# define STARTORIENT EAST

//colors
# define BLACK 0x000000FF
# define GRAY 0x71797EFF
# define MAGENTA 0xFF00FFFF
# define PURPLE 0xB800FFFF
# define WHITE 0xFFFFFFEE
# define PINK 0xFFCCCCFF
# define YELLOW 0xFFFF00FF
# define YEL_WHITE 0xFFFFB6FF
# define YEL_WHITE_SHADE 0xFFFFCCFF
# define RED 0xFF0000FF
# define BLUE 0x0000FFFF
# define SKYBLUE 0x87CEFAEE
# define GREEN 0x00FF00FF
# define BACKG_COLOR 0x000011FF
# define FULL_TRANSPARENT 0x0000000
# define CEILING SKYBLUE
# define FLOOR GRAY

// get next line
# define BUFFER_SIZE 10
# define FD_SIZE 1028

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
	double		hor_dist;
	double		vert_dist;
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
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	t_player		*player;
	t_ray			*ray;
	mlx_key_data_t	keydata;
	int32_t			width;
	int32_t			height;
	int32_t			zoom;
	int				**world_map;
	int				startpos[2];
	double			line_error;
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
int		**load_map(char *mapname, t_data *data);
int		validate_map(int **world_map);
int		validate_mapsquare(int value);
int		color_whole_image(mlx_image_t *img, int color, int width, int height);

//drawing
void	draw_minimap(t_data *data);
int		init_and_draw(t_data *data);
void	put_pixel(t_data *data, t_point *point, mlx_image_t *img);
int		draw_player(t_data *data);
void	apply_rotation(t_data *data, t_point *point, int x, int y);
double	rad(double angle);
void	draw_rays(t_data *data, t_ray *ray);
void	draw_column(t_data *data, t_ray *ray, int i);
void	drw_line(t_point point, t_point dest, t_data *data, mlx_image_t *img);


//keyhook
void	ft_hook_hub(void *param);
t_data	*reinit_image(t_data *data, mlx_image_t *img);

//helper
int		ft_error(char *msg, int	error_code);
int		ft_abs(int result);
int		free_2d_int(int **int_arr);
char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_strcpos(const char *s, int c);
char	*gnl_substr(char *buffer, unsigned int start, size_t len);




#endif
