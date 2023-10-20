SRCS = $(wildcard *.c)

NAME = libft.a

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

INCLUDES = -I../includes

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@ echo "Compiling: $<"
	@$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@ar r $(NAME) $(OBJS)
	@echo "Libft Done !"

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all