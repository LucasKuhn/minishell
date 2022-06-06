NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -g
LDLIBS	=	-lreadline -lft
LDFLAGS	+= 	-L./42-libraries/libft
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c minishell.c prompt.c split_commands.c \
			$(MINIENV) $(BUILTINS) $(EXECUTES) $(REDIRECTS) $(UTILS)
MINIENV =	minienv.c minienv_utils.c minienv_str_utils.c free_minienv.c
BUILTINS =	builtins.c echo.c cd.c pwd.c export.c unset.c env.c exit.c
EXECUTES =	execute_one_command.c execute_multiple_commands.c \
			execute_command.c split_args.c
REDIRECTS =	redirects.c input_redirect.c file_descriptors.c
UTILS =		error.c expand_variables.c quote_checker.c signals.c str_utils.c \
			ft_atoll.c exit_code.c
LIBFT_A	=	./42-libraries/libft/libft.a
HEADER	=	minishell.h
VPATH	=	builtins minienv utils execute src redirects

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

leak: all
	valgrind --suppressions=./local.supp --leak-check=full \
	--show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(NAME)

test: all
	./tests/tester $(NUMBER)
