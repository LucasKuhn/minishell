NAME	=	minishell
CFLAGS	=	-g
ifeq ($(shell uname),Darwin) # MacOS
LDFLAGS	=	-ledit -L/opt/homebrew/opt/libedit/lib
else # Linux
LDFLAGS	=	-lreadline 
endif
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c get_prompt.c builtins.c
LIBFT_A	=	./libft/libft.a
HEADER	=	minishell.h

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

$(LIBFT_A): libft/.git
	make --directory=./libft

libft/.git:
	git submodule update --init --recursive

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft -lft $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(OBJ_DIR):
	mkdir -p $@
