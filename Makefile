NAME	=	minishell
LDFLAGS	=	-lreadline
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c
LIBFT_A	=	./libft/libft.a

all: $(NAME)

run: $(NAME)
	./$(NAME)

$(LIBFT_A):
	git submodule update --init --recursive
	make --directory=./libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT_A)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(OBJ_DIR):
	mkdir -p obj