SRC = $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

INCLUDES = -Iincludes -I/usr/local/Cellar/readline/8.2.1/include/

LINKER = -L./Libft -L/usr/local/Cellar/readline/8.2.1/lib/ -lft -lreadline -lhistory

NAME = minishell

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $< 

$(NAME) : $(OBJ)
	@make -C Libft
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LINKER)

all : $(NAME)

clean :
	@rm -rf $(OBJ)
	@make clean -C Libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C Libft

re : fclean all

.PHONY : all clean fclean re
