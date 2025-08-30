# The name of your executable
NAME = philo

# Compiler and flags
CC = cc
# -Wall -Wextra -Werror are standard 42 flags
# -g for debugging symbols with gdb
# -fsanitize=thread is EXTREMELY useful for detecting race conditions
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread 

# Directories
SRC_DIR = srcs/
INC_DIR = includes/
OBJ_DIR = objs/

# Source files
SRC_FILES = main.c init.c routine.c actions.c monitor.c utils.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

# Object files
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Default rule
all: $(NAME)

# Link the program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile source files into object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean up object files
clean:
	rm -rf $(OBJ_DIR)

# Clean up object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
