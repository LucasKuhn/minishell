NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror -g
LDLIBS	=	-lreadline -lft
LDFLAGS	+= 	-L./42-libraries/libft
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c minishell.c prompt.c split_commands.c \
			$(MINIENV) $(BUILTINS) $(EXECUTES) $(REDIRECTS) $(UTILS) $(EXPANDS)
MINIENV =	minienv.c minienv_utils.c minienv_str_utils.c free_minienv.c
BUILTINS =	builtins_utils.c echo.c cd.c pwd.c export.c unset.c env.c exit.c
EXECUTES =	execute_one_command.c execute_multiple_commands.c wait.c \
			execute_external.c execute_builtin.c split_args.c get_path.c \
			multiple_commands_utils.c
REDIRECTS =	redirects.c input_redirect.c file_descriptors.c pipes.c
UTILS =		error.c quote_checker.c signals.c str_utils.c \
			ft_atoll.c free_array.c arr_len.c
EXPANDS	= 	handle_expansions.c expand_variables.c expand_exit_status.c \
			variables_utils.c
LIBFT_A	=	./42-libraries/libft/libft.a
HEADER	=	minishell.h allowed_libs.h builtins.h errors.h executes.h minienv.h
VPATH	=	builtins minienv utils executes src redirects includes expansions
INCLUDE	=	-I ./ -I ./includes

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
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@

leak: all
	valgrind --suppressions=./local.supp --leak-check=full \
	--show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(NAME)

test: all
	./tests/tester $(NUMBER)
