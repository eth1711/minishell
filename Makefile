SRC = $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)

CC = clang

FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address

RL_PATH = /Users/$(shell whoami)/homebrew/Cellar/readline/8.2.10/

INCLUDES = -Iincludes -I$(RL_PATH)include

LINKER = -L./lib/Libft -L$(RL_PATH)lib -lft -lreadline -lhistory

NAME = minishell

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) $(INCLUDES) -static -c -o $@ $< 

$(NAME) : $(OBJ)
	@make -C lib/Libft
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LINKER)

all : $(NAME)
	@echo Minishell Done !

clean :
	@rm -rf $(OBJ)
	@make clean -C ./lib/Libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ./lib/Libft

re : fclean all

.PHONY : all clean fclean re
