SRC = $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

INCLUDES = -Iincludes 

LINKER = -L./lib/Libft -L./lib/readline -lft -lreadline -lhistory

NAME = minishell

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) -static $(INCLUDES) -c -o $@ $< 

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
