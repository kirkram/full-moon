/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/06/27 17:39:33 by mburakow         ###   ########.fr       */
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

// for future editions and now (dynamic mapsizes)
# define MAX_MAPWIDTH 48
# define MAX_MAPHEIGHT 48
# define SCREENWIDTH 1280
# define SCREENHEIGHT 860
# define MINIZOOM SCREENWIDTH / 120
# define PLAYERSIZE MINIZOOM / 2
# define RESOLUTION 5
# define ANIMATION_SPEED 1.2

# define DEGR 0.0174533
# define DEGR_RESO 0.0174533 / RESOLUTION
# define FOV 60

# define N_PATH "./textures/N.png"
# define S_PATH "./textures/S.png"
# define E_PATH "./textures/E.png"
# define W_PATH "./textures/W.png"
# define TEXTURES_AMOUNT 4

//maths
# define PI 3.14159265359
# define PI_N 4.71238898039
# define PI_S PI / 2
# define PI2 6.28318530718

//direction angle
# define EAST 0
# define SOUTH 90
# define WEST 180
# define NORTH 270

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
	char			**nsew_path; // n s e w
	// mlx_texture_t	*txtrs[TEXTURES_AMOUNT]; // n s e w
	mlx_texture_t	**swordarm_tx;
	mlx_image_t		*swordarm;
	double			last_update;
	mlx_texture_t	**txtrs;
	mlx_texture_t	*txt_n;			
	t_player		*player;
	t_ray			*ray;
	mlx_key_data_t	keydata;
	int32_t			width;
	int32_t			height;
	int32_t			zoom;
	char			*map_path;
	int				**world_map;
	int				map_height;
	int				map_width;
	int				startpos_x;
	int				startpos_y;
	double			line_error;
}					t_data;

typedef struct s_point
{
	int32_t				x;
	int32_t				y;
	uint32_t		color;
	void			*content;
}					t_point;

typedef struct s_textures
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	uint8_t			alpha;
	uint32_t		index;
	double			y;
	double			y_step;
	double			x;
	double			x_step;
	double			save;
	mlx_texture_t	*ptr;
}					t_txt;

//init
void	init_map_data(t_data *data);
int		load_valid_map(t_data *data, int ac, char **av);
void	load_map(t_data *data);
int		validate_map(int **world_map, t_data *data);
void	map_validation_error(char *msg, int rows, char *line, t_data *data);
int		color_whole_image(mlx_image_t *img, int color, int width, int height);
void	free_and_quit(t_data *data);

//drawing
void	draw_minimap(t_data *data);
int		init_and_draw(t_data *data);
void	put_pixel(t_data *data, t_point *point, mlx_image_t *img);
int		draw_player(t_data *data);
void	apply_rotation(t_data *data, t_point *point, int x, int y);
double	rad(double angle);
int		draw_rays(t_data *data, t_ray *ray);
int		draw_column(t_data *data, t_ray *ray, int i);
void	drw_line(t_point point, t_point dest, t_data *data, mlx_image_t *img);

//keyhook
void	ft_hook_hub(void *param);
void 	hook_mouse_move(double x, double y, void* param);
t_data	*reinit_image(t_data *data, mlx_image_t *img);

//helper
int		ft_error(char *msg, int	error_code);
int		ft_abs(int result);
int		**copy_2d_int(int **int_arr, int rows, int cols);
int		free_2d_int(int **int_arr, int rows);
void	print_2d_int(int **int_arr, int rows, int cols);
char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_strcpos(const char *s, int c);
char	*gnl_substr(char *buffer, unsigned int start, size_t len);

#endif
