/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:38:30 by klukiano          #+#    #+#             */
/*   Updated: 2024/09/19 16:41:03 by mburakow         ###   ########.fr       */
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
# define MINIZOOM 5
# define PLAYERSIZE 4
# define RESOLUTION 3
# define ATTACK_SPEED 1.2
# define LINESCALE 1.7
# define MOUSESPEED 0.18
# define ENEMYSPEED 0.7
# define MAX_DELTA 0.05

# define FOV 60
# define COLL 0.3
# define PARALLAX_MULT 3.0

# define DOOR_PATH "./textures/door3.png"
# define FLOOR_PATH "./textures/floor.png"
# define SKY_PATH "./textures/sky.png"
# define MOON_PATH "./textures/moon_xl.png"
# define MAPBACKG_PATH "./textures/mapbackg.png"
# define ENEMY1_SHEET_PATH "./sprites/werewolf_n28b.png"
# define STARTSCREEN_PATH "./textures/fullmoonlogo_px.png"	
# define DEATHSCREEN_PATH "./textures/youdied_new.png"
# define TEXTURES_AMOUNT 7

# define DRAWMINIRAYS 0
# define SHOWFPS 0
# define DRAW_FLOOR 1
# define DRAW_CEILING 0
# define DRAW_STARS 1

// sprites
# define PL_FRAMECOUNT 11
# define EN_FRAMECOUNT 120
# define ESW 96 // enemy sprite width
# define ESH 96 // enemy sprite height
# define ESSW 768 // enemy spritesheet width
# define ESSH 1440 // enemy spritesheet height
# define ESCALE 16.0 // enemy scale

// maths
# define PI 3.14159265359
# define PI_N 4.71238898039
# define PI_S 1.5707963268
# define PI2 6.28318530718
# define EPSILON 1e-6
# define DEGR 0.0174533
# define DEG16 22.5

// skygen
#define NUM_STARS 300

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

typedef struct s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct s_fcoord
{
	float			x;
	float			y;
}					t_fcoord;

typedef struct s_route
{
	t_coord			*coords;
	int				size;
}					t_route;

typedef enum s_enemystate
{
	IDLE,
	WALKING,
	ATTACKING,
	TAKINGDMG,
	DYING,
	DEAD
}					t_enemystate;

typedef struct s_player
{
	mlx_image_t		*img;
	float			x_pos;
	float			y_pos;
	float			x_pos_mini;
	float			y_pos_mini;
	float			angle;
	float			prev_angle; // starry sky render
	int32_t			imgwidth;
	int32_t			imgheight;
	int				hitpoints;
	bool			attacked;
	bool			is_dead;
}					t_player;

typedef struct s_enemy
{
	float			x_pos;
	float			y_pos;
	float			x_target;
	float			y_target;
	float			distance;
	float			angle;
	float			rel_angle;
	int				current_frame;
	int				visible;
	t_enemystate	state;
	int				hitpoints;
	double			last_frame;
	double			last_route;
	float			scale;
	t_ray			ray;
	int				dof;
	bool			seen_player;
	float			speed;
	t_route			*route;
	bool			attacked;
}					t_enemy;

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

typedef struct s_star
{
    float			angle;
    int				height;
    uint16_t		brightness;
	double			timer;
	double			blinkspeed;
	uint8_t 		red;
	uint8_t         green;
	uint8_t         blue;
} 					t_star;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*minimap;
	mlx_image_t		*minimap_img;
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	mlx_image_t		*startscreen;
	double 			starttime;
	mlx_image_t		*deathscreen;
	t_star			stars[NUM_STARS];
	mlx_texture_t	*moon_txt;
	mlx_image_t		*moon;
	int				moon_yposneg;
	int				moon_xpos;
	float			moon_angle;
	unsigned int	ceilingcolor;
	unsigned int	floorcolor;
	char			**nsew_path;
	mlx_texture_t	**swordarm_tx;
	mlx_image_t		*swordarm;
	double			last_update;
	double			last_attack;
	mlx_texture_t	**txtrs;
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
	t_map			keyhook_map;
	t_point			draw_points;
	t_txt			draw_txt;
}					t_data;

// init
void				init_map_data(t_data *data);
void				load_textures(t_data *data);
void				init_player_data(t_player *player);
int					create_fname(char *fname, int i);
int					load_valid_map(t_data *data, int ac, char **av);
void				load_map(t_data *data);
int					validate_map(int **world_map, t_data *data);
int					validate_mapsquare(int value);
void				convert_tabs(char **line);
void				add_new_enemy(int x, int y, t_data *data, char *line);
void				fill_with_nines(t_data *data, int y, int x);
void				count_mapdimensions(t_data *data);
int					get_player_startpos(int x, int y, t_data *data, char *line);
int					flood_fill(int pos_y, int pos_x, int **wmap, t_data *data);
void				read_map_parameter(char *line, t_data *data);
void				map_validation_error(char *msg, int rows, char *line,
						t_data *data);
int					color_whole_image(mlx_image_t *img, int color, int width,
						int height);
void				generate_stars(t_data *data);
void				free_all_and_quit(t_data *data, char *msg, int exitcode);

// drawing
void				draw_minimap(t_data *data);
int					init_and_draw(t_data *data);
int					put_background(t_data *data);
int					init_player(t_data *data);
int					init_enemy_frames(t_data *data);
void				update_enemy_frame(t_enemy *enemy, t_data *data);
void				put_pixel(t_data *data, t_point *point, mlx_image_t *img);
uint32_t			get_a(uint32_t rgba);
uint32_t			get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
int					draw_player_minimap(t_data *data);
float				init_walls_values(t_data *data, t_ray *ray, t_txt *txt,
						t_point *line);
void				find_txt_for_floors_ceiling(t_data *data, t_txt *txt,
						t_ray *ray, float dfm);
void				assign_texture_to_walls(t_data *data, t_ray *ray,
						t_txt *txt);
void				draw_world(t_data *data);
void				drw_line(t_point point, t_point dest, t_data *data,
						mlx_image_t *img);
uint32_t			index_color(t_txt *txt, t_ray *ray, bool is_wall);
uint32_t			index_color_floor(t_txt *txt, t_ray *ray,
						float dist_from_middle, t_data *data);
void				horizontal_rays(t_data *data, t_ray *ray);
void				vertical_rays(t_data *data, t_ray *ray);
void				calc_distance(t_data *data, t_ray *ray);
void				draw_minirays(t_data *data, t_ray *ray);
void				fix_fisheye(t_data *data, t_ray *ray);
int					is_equal(float a, float b);
int					check_walls(t_data *data, t_ray *ray, t_map *map,
						bool is_vert);
void				increment_offset(t_data *data, t_ray *ray, bool is_vert);
void 				render_stars(t_data *data) ;
void				draw_star(int x, int y, t_star *star, t_data *data);
uint32_t 			get_star_color(uint16_t brightness, t_star *star);
void				render_moon(t_data *data);
void 				copy_image_to_image(mlx_image_t *dest, mlx_image_t *src, int dx, int dy);


// keyhook
void				ft_hook_hub(void *param);
void				hook_mouse_move(double x, double y, void *param);
void				movement_loop(t_data *data);
void				open_door(t_data *data);
void				hook_player_animation(t_data *data);
void				hit_enemy_if_in_range(t_data *data);
void				calc_collision_ad(t_data *data, t_map *map, bool left);
void				calc_collision_ws(t_data *data, t_map *map, bool forward);

// enemy
void				hook_enemies(t_data *data);
void				sort_enemy_arr(t_data *data);
void				find_enemy_rays(t_data *data, t_enemy *enemy);
bool				enemy_is_alive(t_enemy *enemy);
void				draw_minirays_enemy(t_data *data, t_ray *ray,
						t_enemy *enemy);
int					check_player(t_data *data, t_ray *ray, t_map *map,
						t_enemy *enemy);
void				calc_distance_enemy(t_ray *ray, t_enemy *enemy);
void				get_rel_angle_and_pos(t_enemy *enemy, t_data *data);
void				calculate_enemy_angle(t_enemy *enemy);
void				update_enemy_frame(t_enemy *enemy, t_data *data);
void				update_idle_frame(t_enemy *enemy, int index, double now,
						double prev);
void				update_walking_frame(t_enemy *enemy, int index, double now,
						double prev);
void				update_attacking_frame(t_enemy *enemy, int index, double now,
						double prev);
void				update_taking_damage_frame(t_enemy *enemy, int index, 
						double now, double prev);
void				update_dying_frame(t_enemy *enemy, double now, double prev);
void				update_enemy(t_enemy *enemy, t_data *data);
void				update_enemy_target(t_enemy *enemy, t_coord player_pos,
						t_coord enemy_pos, t_data *data);
int					has_reached_target(t_enemy *enemy);
void				initialize_enemy_route(t_enemy *enemy, t_coord player_pos,
						t_coord enemy_pos, t_data *data);
void				step_route(t_enemy *enemy);
void				draw_enemy_onto_canvas(t_enemy *enemy, int dest_x,
						int dest_y, t_data *data);
void				move_enemy(t_data *data, t_enemy *enemy);
void				move_enemy_position(t_data *data, t_enemy *enemy,
						t_fcoord direction, float delta_time);

// helper
int					ft_error(char *msg, int error_code);
int					ft_abs(int result);
float				degr(float angle);
float				rad(float angle);
int					min(int a, int b);
float				normalize_degr(float angle);
float				normalize_rad(float angle);
void				free_textures(t_data *data);
void				free_enemies(t_data *data);
int					is_valid_hex(const char *hex_str);
char				*get_next_line(int fd);
void				angle_outofbounds_check(t_ray *ray);
void				*ft_realloc(void *ptr, size_t new_size);
float				angle_difference_rad(float angle1, float angle2);

// maptools
int					**alloc_2d_int(int rows, int cols);
int					**copy_2d_int(int **int_arr, int rows, int cols);
int					free_2d_int(int **int_arr, int rows);
void				print_2d_int(int **int_arr, int rows, int cols);
int					free_2d_char(char **str_arr);

// pathfinding
t_route				*a_star(t_coord start_pos, t_coord end_pos, t_data *data);

#endif
