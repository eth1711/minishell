SRC = $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDES = -Iincludes

LINKER = -L./Libft -lft -lreadline

NAME = minishell

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME) : $(OBJ)
	@make -C Libft
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LINKER)

all : $(NAME)

clean :
	@rm -rf $(OBJ)
	@make clean -C Libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C Libft

re : fclean all

.PHONY : all clean fclean re
