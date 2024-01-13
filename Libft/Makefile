SRCS = $(wildcard *.c)

NAME = libft.a

OBJS = $(SRCS:.c=.o)

OBJS_DIR = objs/
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS))

INCLUDES = -I../includes

CC = gcc

FLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c
	@mkdir -p objs
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS_PREF)
	@ar rc $(NAME) $(OBJS_PREF)
	@echo "Libft Done !"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo Libft clean !

fclean: clean
	@rm -f $(NAME)
	@echo Libft fclean !

re: fclean all

.PHONY : all clean fclean re