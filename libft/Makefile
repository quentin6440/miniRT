CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = 	ft_bzero.c \
      	ft_calloc.c \
	    ft_putchar_fd.c \
      	ft_putendl_fd.c \
      	ft_putnbr_fd.c \
      	ft_putstr_fd.c \
		ft_atoi_strict.c \
		ft_atof.c \
		ft_isspace.c \
      	ft_strlen.c \
		ft_strchr.c \
      	ft_strncmp.c \
		ft_strtrim.c \
		ft_strdup.c \
      	ft_substr.c \
		ft_split.c \
      	get_next_line.c

OBJ_DIR = build
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) -rcs $@ $(OBJ)

$(OBJ_DIR)/%.o: %.c libft.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
