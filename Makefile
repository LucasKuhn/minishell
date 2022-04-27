NAME	=	minishell
LDFLAGS	=	-lreadline
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c


all: $(NAME)

run: $(NAME)
	./$(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

$(OBJ_DIR):
	mkdir -p obj