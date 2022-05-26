NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -g
LDLIBS	=	-lreadline -lft
LDFLAGS	+= 	-L./42-libraries/libft
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c prompt.c str_utils.c \
			execute_command.c signals.c split_args.c \
			split_commands.c quote_checker.c redirects.c \
			minishell.c executes.c expand_variables.c \
			$(MINIENV) $(BUILTINS)
MINIENV = minienv.c minienv_utils.c minienv_str_utils.c free_minienv.c
BUILTINS =	builtins.c echo.c cd.c pwd.c export.c unset.c env.c exit.c
LIBFT_A	=	./42-libraries/libft/libft.a
HEADER	=	minishell.h
VPATH	=	builtins minienv utils execute src

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

leak:
	valgrind --suppressions=./local.supp --leak-check=full \
	--show-leak-kinds=all ./$(NAME)
