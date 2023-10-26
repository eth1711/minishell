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

$(LIBFT) :
	@Make -C ./Libft

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(INCLUDES) $(LINKER) $(OBJ) -o $(NAME)

all : $(LIBFT) $(NAME)

clean :
	@rm -rf $(OBJ)
	@Make clean -C ./Libft

fclean : clean
	@rm -rf $(NAME)
	@Make fclean -C ./Libft

re : fclean all

.PHONY : all clean fclean re