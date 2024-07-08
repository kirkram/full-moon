NAME = libft.a
CFLAGS = -O2 -Wall -Wextra -Werror
SRCS =  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c\
    ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c\
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c\
    ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcpos.c\
	ft_atoh.c get_next_line_bonus.c
BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c 
OBJCTS = $(SRCS:.c=.o)
BONUS_OBJCTS = $(BONUS_SRCS:.c=.o)
LIBCR = ar rc libft.a $(OBJCTS)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJCTS)
	$(LIBCR)

bonus: .bonus

.bonus: $(NAME) $(BONUS_OBJCTS)
	$(LIBCR) $(BONUS_OBJCTS)
	touch .bonus

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJCTS) $(BONUS_OBJCTS)
	$(RM) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all
