/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klukiano <klukiano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/09 17:31:42 by klukiano         ###   ########.fr       */
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

//FOR DEBUGGING DEL
# include <sys/time.h>

//FOR DEBUGGIN
unsigned long	current_time(void);

# define MAX_MAPWIDTH 256
# define MAX_MAPHEIGHT 256
# define SCREENWIDTH 1280 
# define SCREENHEIGHT 860 
# define MINIZOOM SCREENWIDTH / 150
# define PLAYERSIZE MINIZOOM / 2
# define RESOLUTION 3
# define ANIMATION_SPEED 1.2

# define DEGR 0.0174533
# define DEGR_RESO 0.0174533 / RESOLUTION
# define FOV 60
# define COLL 0.3

# define N_PATH "./textures/cat.png"
# define S_PATH "./textures/gradient.png"
# define E_PATH "./textures/green.png"
# define W_PATH "./textures/tiger.png"
# define DOOR_PATH "./textures/door.png"
# define TEXTURES_AMOUNT 5

# define MAPBACKG_PATH "./textures/mapbackg.png"

//sprites
# define PL_FRAMECOUNT 11
# define EN_FRAMECOUNT 64
# define ESW 74	// enemy sprite width
# define ESH 81	// enemy sprite height
# define ESSW 592 // enemy spritesheet width
# define ESSH 648 // enemy spritesheet height

//maths
# define PI 3.14159265359
# define PI_N 4.71238898039
# define PI_S 1.5707963268
# define PI2 6.28318530718
# define EPSILON 1e-6

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

# define TAB_WIDTH 4

typedef struct s_map
{
	int16_t	x;
	int16_t	y;
}	t_map;

typedef struct s_ray
{
	float		x;
	float		y;
	float		x_v;
	float		y_v;
	float		hor_dist;
	float		vert_dist;
	float		dist;
	float		ang;
	float		atan;
	float		ntan;
	float		y_off;
	float		x_off;
	int16_t		dof;
	int			is_doorv;
	int			is_doorh;
}				t_ray;

typedef struct s_player
{
	mlx_image_t		*img;
	float			x_pos;
	float			y_pos;
	float			x_pos_mini;
	float			y_pos_mini;
	float			angle;
	int32_t			imgwidth;
	int32_t			imgheight;
}					t_player;

typedef struct s_enemy
{
	float			x_pos;
	float			y_pos;
	float			distance;
	float			rel_angle;
	float			start_ang;
	float			end_ang;
	float			start_posx;
	float			end_posx;
	int				current_frame;
	int				visible;
}					t_enemy;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*minimap_img;
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	//mlx_texture_t	*door;
	unsigned int	ceilingcolor;
	unsigned int 	floorcolor;
	char			**nsew_path;
	mlx_texture_t	**swordarm_tx;
	mlx_image_t		*swordarm;
	double			last_update;
	double			last_attack;
	mlx_texture_t	**txtrs;
	mlx_texture_t	*txt_n;
	t_player		*player;
	t_ray			*ray;
	float			raydis[FOV * RESOLUTION];
    mlx_image_t*    drawframe;
	mlx_key_data_t	keydata;
	int32_t			width;
	int32_t			height;
	int32_t			zoom;
	float			speed;
	char			*map_path;
	int				**world_map;
	int				map_height;
	int				map_width;
	int				startpos_x;
	int				startpos_y;
	t_enemy			**enemies;
	mlx_texture_t	*enemy_ssheet;
	mlx_image_t		**enemy_frame;
	mlx_image_t		*enemy_img;
	int				ess_width;
	int				ess_height;
	float			line_error;
}					t_data;

typedef struct s_point
{
	int32_t			x;
	int32_t			y;
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
	uint32_t		maxindex;
	float			y;
	float			y_step;
	float			x;
	float			x_step;
	float			save;
	mlx_texture_t	*ptr;
}					t_txt;

//init
void	init_map_data(t_data *data);
int		create_fname(char *fname, int i);
int		load_valid_map(t_data *data, int ac, char **av);
void	load_map(t_data *data);
int		validate_map(int **world_map, t_data *data);
int		validate_mapsquare(int value);
void	convert_tabs(char **line);
void	add_new_enemy(int x, int y, t_data *data, char *line);
void	fill_with_ones(t_data *data, int y, int x);
void	count_mapdimensions(t_data *data);
int		get_player_startpos(int x, int y, t_data *data, char *line);
int		flood_fill(int pos_y, int pos_x, int **wmap, t_data *data);
void	read_map_parameter(char *line, t_data *data);
void	map_validation_error(char *msg, int rows, char *line, t_data *data);
int		color_whole_image(mlx_image_t *img, int color, int width, int height);
void	free_all_and_quit(t_data *data, char *msg, int exitcode);

//drawing
int		draw_minimap(t_data *data);
int		init_and_draw(t_data *data);
int		put_background(t_data *data);
int		redraw_background(t_data *data);
int		init_player(t_data *data);
int		init_enemy_frames(t_data *data);
void	put_pixel(t_data *data, t_point *point, mlx_image_t *img);
int		draw_player_minimap(t_data *data);
void	draw_sprites(t_data *data);
void	apply_rotation(t_data *data, t_point *point, int x, int y);
float	rad(float angle);
int		draw_rays(t_data *data);
void	drw_line(t_point point, t_point dest, t_data *data, mlx_image_t *img);

//keyhook
void	ft_hook_hub(void *param);
void 	hook_mouse_move(double x, double y, void* param);
void	hook_mouse_button(mouse_key_t button, action_t action, 
			modifier_key_t mods, void *param);

//enemy
void	hook_enemies(t_data *data);
void	sort_enemy_arr(t_data *data);

//animation
void	attack_animation(t_data *data);

//helper
int		ft_error(char *msg, int	error_code);
int		ft_abs(int result);
void	free_textures(t_data *data);
void	free_enemies(t_data *data);
int		is_valid_hex(const char *hex_str);
char	*get_next_line(int fd);

//maptools
int		**copy_2d_int(int **int_arr, int rows, int cols);
int		free_2d_int(int **int_arr, int rows);
void	print_2d_int(int **int_arr, int rows, int cols);

#endif
