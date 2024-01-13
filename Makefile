SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc

LIBFT = libft.a

FLAGS = -Wall -Werror -Wextra

INCLUDES = -Iincludes

LINKER = -lreadline -L./Libft -lft

NAME = minishell

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(NAME) : $(OBJ)
	@make -C Libft
	@$(CC) $(FLAGS) $(INCLUDES) $(LINKER) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	@rm -rf $(OBJ)
	@make clean -C Libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C Libft

re : fclean all

.PHONY : all clean fclean re
