SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDES = -Iincludes

LINKER = -lreadline -L./Libft -lft

NAME = minishell

%.o : %.c
	@echo Compiling $<
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(NAME) : $(OBJ)
	Make -C ./Libft
	@$(CC) $(FLAGS) $(INCLUDES) $(LINKER) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	@rm $(OBJ)
	Make clean -C ./Libft

fclean : clean
	@rm $(NAME)
	Make fclean -C ./Libft

re : fclean all

.PHONY : all clean fclean