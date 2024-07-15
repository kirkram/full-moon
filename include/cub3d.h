/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/07/15 19:50:48 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// FOR DEBUGGING DEL
# include <sys/time.h>

// FOR DEBUGGIN
unsigned long		current_time(void);

# define MAX_MAPWIDTH 256
# define MAX_MAPHEIGHT 256
# define SCREENWIDTH 1280
# define SCREENHEIGHT 860
# define MINIZOOM 150
# define PLAYERSIZE 4
# define RESOLUTION 3
# define ANIMATION_SPEED 1.2
# define LINESCALE 1.7
# define MOUSESPEED 0.8

# define FOV 60
# define COLL 0.3

# define DOOR_PATH "./textures/door.png"
# define TEXTURES_AMOUNT 5

# define MAPBACKG_PATH "./textures/mapbackg.png"
# define DRAWMINIRAYS 0

// sprites
# define PL_FRAMECOUNT 11
# define EN_FRAMECOUNT 64
# define ESW 74 // enemy sprite width
# define ESH 81 // enemy sprite height
# define ESSW 592 // enemy spritesheet width
# define ESSH 648 // enemy spritesheet height

// maths
# define PI 3.14159265359
# define PI_N 4.71238898039
# define PI_S 1.5707963268
# define PI2 6.28318530718
# define EPSILON 1e-6
# define DEGR 0.0174533

// direction angle
# define EAST 0
# define SOUTH 90
# define WEST 180
# define NORTH 270

// colors
# define BLACK 0x000000FF
# define GRAY 0x71797EFF
# define WHITE 0xFFFFFFEE
# define YELLOW 0xFFFF00FF
# define RED 0xFF0000FF
# define BLUE 0x0000FFFF
# define SKYBLUE 0x87CEFAEE
# define GREEN 0x00FF00FF
# define FULL_TRANSPARENT 0x0000000
# define CEILING SKYBLUE
# define FLOOR GRAY

// get next line
# define BUFFER_SIZE 10
# define FD_SIZE 1028

# define TAB_WIDTH 4

typedef struct s_map
{
	int16_t			x;
	int16_t			y;
}					t_map;

typedef struct s_ray
{
	float			x;
	float			y;
	float			x_v;
	float			y_v;
	float			hor_dist;
	float			vert_dist;
	float			dist;
	float			ang;
	float			atan;
	float			ntan;
	float			y_off;
	float			x_off;
	int16_t			dof;
	bool			is_doorv;
	bool			is_doorh;
	int32_t			range;
}					t_ray;

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
	float			scale;
}					t_enemy;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*minimap_img;
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	unsigned int	ceilingcolor;
	unsigned int	floorcolor;
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
	mlx_image_t		*drawframe;
	mlx_key_data_t	keydata;
	uint32_t		width;
	uint32_t		height;
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
	int				ess_width;
	int				ess_height;
	float			line_error;
	struct timespec last_time;
    double 			fps;
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
	float			y;
	float			y_step;
	float			x;
	float			x_step;
	mlx_texture_t	*ptr;
}					t_txt;

// init
void				init_map_data(t_data *data);
int					create_fname(char *fname, int i);
int					load_valid_map(t_data *data, int ac, char **av);
void				load_map(t_data *data);
int					validate_map(int **world_map, t_data *data);
int					validate_mapsquare(int value);
void				convert_tabs(char **line);
void				add_new_enemy(int x, int y, t_data *data, char *line);
void				fill_with_ones(t_data *data, int y, int x);
void				count_mapdimensions(t_data *data);
int					get_player_startpos(int x, int y, t_data *data, char *line);
int					flood_fill(int pos_y, int pos_x, int **wmap, t_data *data);
void				read_map_parameter(char *line, t_data *data);
void				map_validation_error(char *msg, int rows, char *line,
						t_data *data);
int					color_whole_image(mlx_image_t *img, int color, int width,
						int height);
void				free_all_and_quit(t_data *data, char *msg, int exitcode);

// drawing
void				draw_minimap(t_data *data);
int					init_and_draw(t_data *data);
int					put_background(t_data *data);
int					init_player(t_data *data);
int					init_enemy_frames(t_data *data);
void				put_pixel(t_data *data, t_point *point, mlx_image_t *img);
uint32_t			get_a(uint32_t rgba);
uint32_t			get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
int					draw_player_minimap(t_data *data);
void				draw_sprites(t_data *data);
void				assign_texture_to_ray(t_data *data, t_ray *ray, t_txt *txt);
float				rad(float angle);
void				draw_rays(t_data *data);
void				drw_line(t_point point, t_point dest, t_data *data,
						mlx_image_t *img);
uint32_t			index_color(t_txt *txt, t_ray *ray);
void				horizontal_rays(t_data *data, t_ray *ray);
void				vertical_rays(t_data *data, t_ray *ray);
void				calc_distance(t_data *data, t_ray *ray);
void				draw_minirays(t_data *data, t_ray *ray);
void				fix_fisheye(t_data *data, t_ray *ray);
int					is_equal(float a, float b);
int					check_walls(t_data *data, t_ray *ray, t_map *map,
						bool is_vert);
void				increment_offset(t_data *data, t_ray *ray, bool is_vert);

// keyhook
void				ft_hook_hub(void *param);
void				hook_mouse_move(double x, double y, void *param);
void				movement_loop(t_data *data, t_map *map);
void				open_door(t_data *data, t_map *map);
void				calc_collision_ad(t_data *data, t_map *map, bool left);
void				calc_collision_ws(t_data *data, t_map *map, bool forward);

// enemy
void				hook_enemies(t_data *data);
void				sort_enemy_arr(t_data *data);

// animation
void				attack_animation(t_data *data);

// helper
int					ft_error(char *msg, int error_code);
int					ft_abs(int result);
void				free_textures(t_data *data);
void				free_enemies(t_data *data);
int					is_valid_hex(const char *hex_str);
char				*get_next_line(int fd);
void				angle_outofbounds_check(t_ray *ray);

// maptools
int					**copy_2d_int(int **int_arr, int rows, int cols);
int					free_2d_int(int **int_arr, int rows);
void				print_2d_int(int **int_arr, int rows, int cols);

#endif
