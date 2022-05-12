NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -g
LDLIBS	=	-lreadline -lft
LDFLAGS	+= 	-L./42-libraries/libft
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c prompt.c minienv.c minienv_utils.c str_utils.c \
			execute_command.c list_utils.c signals.c split_args.c $(BUILTINS)
BUILTINS =	builtins.c echo.c cd.c pwd.c export.c unset.c env.c exit.c
LIBFT_A	=	./42-libraries/libft/libft.a
HEADER	=	minishell.h
VPATH	=	builtins

all: $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf obj
	@echo "removed obj folder"

fclean: clean
	@rm -rf $(NAME)
	@echo "removed executable"

re: fclean all

$(LIBFT_A):
	git submodule update --init --recursive
	make --directory=./42-libraries/libft

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(OBJ_DIR):
	mkdir -p $@
