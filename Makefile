SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDES = -Iminishell.h -I

NAME = minishell

%.o : %.c
$(CC) $(FLAGS) $(INCLUDES) $> -o $@

$(NAME) : $(OBJ) minishell.h
$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	rm $(OBJ)

fclean : clean
	rm $(NAME)

re : fclean all

.PHONY : all clean fclean