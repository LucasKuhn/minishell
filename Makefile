NAME	=	minishell
CFLAGS	=	-g
LDFLAGS	=	-ledit 
ifeq ($(shell uname),Darwin) # MacOS
LDFLAGS	+=	-L/opt/homebrew/opt/libedit/lib  
endif
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c get_prompt.c builtins.c
LIBFT_A	=	./libft/libft.a

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
	make --directory=./libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) -L./libft -lft

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(OBJ_DIR):
	mkdir -p $@