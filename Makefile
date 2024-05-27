NAME = cub3d
LIBFT_PATH = ./lib/libft
LIBMLX_PATH	= ./lib/MLX42
LIBFT = ./lib/libft/libft.a
LIBMLX42 = ./lib/MLX42/build/libmlx42.a
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code #-lm
HEADERS	= -I ./include -I ./lib/MLX42/include/ -I ./lib/get_next_line/ -I "/Users/klukiano/.brew/opt/glfw/include"
DEBUGFLAGS = -g -fsanitize=address,undefined,integer
LIBS	= ./lib/MLX42/build/libmlx42.a -L/Users/klukiano/.brew/lib/ -lglfw -framework Cocoa -framework OpenGL -framework IOKit
SRCS = ./src/main.c
OBJCTS = $(SRCS:.c=.o)
BONUS_OBJCTS = $(BONUS_SRCS:.c=.o)
GNL_OBJCTS = $(GNL_SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX42) $(OBJCTS) 
	cc $(CFLAGS) $(HEADERS) $(OBJCTS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBMLX42): .libmlx42

.libmlx42:
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4
	touch .libmlx42

$(LIBFT):
	make -C $(LIBFT_PATH)

debug: .debug

.debug: $(LIBMLX42) $(OBJCTS)
	cc $(DEBUGFLAGS) $(HEADERS) $(OBJCTS) $(LIBFT) $(LIBS)  -o debug.out
	touch .debug

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ $(HEADERS)

both: $(NAME) bonus

clean: 
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJCTS) $(BONUS_OBJCTS)
	
fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	$(RM) debug.out
	$(RM) .debug
	$(RM) .bonus
	$(RM) .libmlx42
	$(RM) -r $(LIBMLX_PATH)/build

re: fclean all

.PHONY: all clean fclean re bonus both debug libmlx42