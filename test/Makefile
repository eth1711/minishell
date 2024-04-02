SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = #-Wall -Werror -Wextra -fsanitize=address -g3

INCLUDES = -Iincludes -I/usr/local/Cellar/readline/8.2.1/include/

LINKER = -L/usr/local/Cellar/readline/8.2.1/lib/ -lreadline -lhistory

NAME = test

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $< 

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LINKER)

all : $(NAME)
	@echo Minishell Done !

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
