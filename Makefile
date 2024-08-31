NAME = cub3D
BONUS_NAME = cub3D_bonus
LIBFT_PATH = ./lib/libft
LIBMLX_PATH = ./lib/MLX42
LIBMLX_REPO = https://github.com/codam-coding-college/MLX42.git
LIBFT = $(LIBFT_PATH)/libft.a
LIBMLX42 = $(LIBMLX_PATH)/build/libmlx42.a
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code 
HEADERS = -O2 -I ./include -I $(LIBMLX_PATH)/include/ -I /usr/local/Cellar/glfw/include
DEBUGFLAGS = -g -o -fsanitize=address,undefined 
LIBS = $(LIBMLX42) -lm -lglfw -L /Users/$(USER)/.brew/opt/glfw -L/Users/$(USER)/.brew/lib -L/opt/homebrew/lib #-framework Cocoa -framework OpenGL -framework IOKit
SRC_DIR = 	./srcs
SRCS = main.c helper.c helper2.c helper_angle.c \
drawing.c drawing_2.c drawing_distance.c drawing_helper.c drawing_hor_rays.c drawing_minimap.c drawing_textures.c drawing_vert_rays.c \
init.c init2.c init3.c init_loadtex.c\
keyhook.c keyhook_movement.c keyhook_movement_2.c keyhook_anim.c \
minimap.c maploader.c maploader2.c maploader3.c maploader4.c \
mapvalidator.c mapvalidator_floodfill.c maptools.c map_params.c map_params2.c exitfree.c \
enemy.c enemy_helper.c enemy_draw.c enemy_sort.c enemy_rays.c enemy_rays_2.c enemy_move.c enemy_move2.c \
enemy_frame.c enemy_frame2.c enemy_update.c enemy_update2.c astar.c astar_pq_queue.c astar_checked.c \
astar_pq_tools.c astar_utils.c astar_path.c astar_init_clean.c ft_realloc.c
BONUS_SRCS = main.c helper.c helper2.c helper_angle.c \
drawing_bonus.c drawing_2.c drawing_distance.c drawing_helper.c drawing_hor_rays.c drawing_minimap.c drawing_textures.c drawing_vert_rays.c \
init.c init2.c init3.c init_loadtex.c\
keyhook.c keyhook_movement.c keyhook_movement_2.c keyhook_anim.c \
minimap.c maploader.c maploader2.c maploader3.c	maploader4.c \
mapvalidator.c mapvalidator_floodfill.c maptools.c map_params.c map_params2.c exitfree.c \
enemy.c enemy_helper.c enemy_draw.c enemy_sort.c enemy_rays.c enemy_rays_2.c enemy_move.c enemy_move2.c \
enemy_frame.c enemy_frame2.c enemy_update.c enemy_update2.c astar.c astar_pq_queue.c astar_checked.c \
astar_pq_tools.c astar_utils.c astar_path.c astar_init_clean.c ft_realloc.c
INC_DIRS = ./include $(LIBMLX_PATH)/include/ $(LIBFT_PATH)/libft $(LIBFT_PATH)/ft_printf/incs /usr/local/Cellar/glfw/include
INCS = $(foreach dir, $(INC_DIRS), -I $(dir))
OBJ_DIR = ./objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)
RM = rm -f

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	cc $(CFLAGS) $(INCS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX42) $(OBJ_DIR) $(OBJS) 
	cc $(CFLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBMLX42): .libmlx42

$(LIBMLX42D): .libmlx42d

.libmlx42: clone_mlx42
	@if [ ! -f .libmlx42 ]; then \
		echo "Building MLX42 library..."; \
		cd $(LIBMLX_PATH) && cmake -B build && make -C build -j4 || exit 1; \
		cd ../../; \
		touch .libmlx42; \
	else \
		echo "MLX42 library is already built."; \
	fi

.libmlx42d: clone_mlx42
	cd $(LIBMLX_PATH) && cmake -DDEBUG=1 -B build && make -DDEBUG=1 -C build -j4
	touch .libmlx42d

clone_mlx42:
	@if [ ! -d "$(LIBMLX_PATH)" ]; then \
		echo "Cloning MLX42 library..."; \
		git clone $(LIBMLX_REPO) $(LIBMLX_PATH); \
	else \
		echo "MLX42 library already exists."; \
	fi

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus: .bonus

.bonus: $(LIBFT) $(LIBMLX42) $(OBJ_DIR) $(BONUS_OBJS)
	cc $(CFLAGS) $(HEADERS) $(BONUS_OBJS) $(LIBFT) $(LIBS) -o $(BONUS_NAME)
	touch .bonus

debug: .debug

.debug: $(LIBFT) $(LIBMLX42D) $(OBJ_DIR) $(OBJS) 
	cc $(DEBUGFLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(LIBS) -o debug.out
	touch .debug

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ $(HEADERS)

both: $(NAME) bonus

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	$(RM) debug.out
	$(RM) .debug
	$(RM) .bonus
	$(RM) .libmlx42
	$(RM) .libmlx42d
	$(RM) -r $(LIBMLX_PATH)/build
	$(RM) -r $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re bonus both debug libmlx42 clone_mlx42
