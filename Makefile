SRC = $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

USER = $(shell whoami)

INCLUDES = -Iincludes -I/Users/$(USER)/homebrew/Cellar/readline/8.2.10/include/

LINKER = -L/Users/$(USER)/homebrew/Cellar/readline/8.2.10/lib/ -L./Libft -lft -lreadline -lhistory

NAME = minishell

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) -static $(INCLUDES) -c -o $@ $< 

$(NAME) : $(OBJ)
	@make -C Libft
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LINKER)

all : $(NAME)
	@echo Minishell Done !

clean :
	@rm -rf $(OBJ)
	@make clean -C Libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C Libft

re : fclean all

.PHONY : all clean fclean re
