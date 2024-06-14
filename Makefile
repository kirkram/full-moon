NAME = cub3d
LIBFT_PATH = ./lib/libft
LIBMLX_PATH = ./lib/MLX42
LIBFT = $(LIBFT_PATH)/libft.a
LIBMLX42 = $(LIBMLX_PATH)/build/libmlx42.a
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code
HEADERS = -I ./include -I $(LIBMLX_PATH)/include/ -I /usr/local/Cellar/glfw/include
DEBUGFLAGS = -g -fsanitize=address,undefined,integer
LIBS = $(LIBMLX42) -L /Users/$(USER)/.brew/opt/glfw -L/Users/$(USER)/.brew/lib -L/opt/homebrew/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
SRC_DIR = ./srcs
SRCS = main.c helper.c drawing.c init.c keyhook.c minimap.c maploader.c get_next_line_bonus.c
INC_DIRS = ./include $(LIBMLX_PATH)/include/ $(LIBFT_PATH)/libft $(LIBFT_PATH)/ft_printf/incs /usr/local/Cellar/glfw/include
INCS = $(foreach dir, $(INC_DIRS), -I $(dir))
OBJ_DIR = ./objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
#OBJCTS = $(SRCS:.c=.o)
#BONUS_OBJCTS = $(BONUS_SRCS:.c=.o)
#GNL_OBJCTS = $(GNL_SRCS:.c=.o)
RM = rm -f

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				cc $(CFLAGS) $(INCS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX42) $(OBJ_DIR) $(OBJS)
	cc $(CFLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBMLX42): .libmlx42

.libmlx42:
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4
	touch .libmlx42

clone_mlx42:
	if [ ! -d "$(LIBMLX_PATH)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git "$(LIBMLX_PATH)"; \
	fi

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

debug: .debug

.debug: $(LIBFT) $(LIBMLX42) $(OBJS)
	cc $(DEBUGFLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(LIBS) -o debug.out
	touch .debug

%.o: %.c ./include/cub3d.h
	cc $(CFLAGS) -c $< -o $@ $(HEADERS)

both: $(NAME) bonus

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	$(RM) debug.out
	$(RM) .debug
	$(RM) .bonus
	$(RM) .libmlx42
	$(RM) -r $(LIBMLX_PATH)/build
	$(RM) -r $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re bonus both debug libmlx42