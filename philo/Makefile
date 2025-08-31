NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=thread 

SRC_DIR = srcs/
INC_DIR = includes/
OBJ_DIR = objs/

SRC_FILES = main.c init.c routine.c checker.c monitor.c utils.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
