#
# Makefile for the 42 project "philosophers" (Bonus part)
#

# --- Variables ---

# The name of your final executable
NAME = philo_bonus

# The compiler to use
CC = cc

# The command to remove files
RM = rm -f

# Compiler flags:
# -Wall -Wextra -Werror: The standard 42 flags for maximum warnings.
# -pthread: Essential for compiling semaphore and thread functions.
# -g: Adds debugging symbols (for use with gdb/lldb).
# -fsanitize=thread: A powerful tool to detect data races at runtime.
#                    Highly recommended for this project.
CFLAGS = -Wall -Wextra -Werror -pthread -g -Iinclude

# --- Files ---

# List of your source (.c) files.
# !!! IMPORTANT: You MUST update this list with your actual file names.
SRCS =  src/main_bonus.c \
        src/init_bonus.c \
        src/routine_bonus.c \
        src/utils_bonus.c

# List of your header (.h) files.
HDRS = philo_bonus.h

# Object (.o) files are automatically generated from the source files list.
# The following line replaces every ".c" extension with ".o".
OBJS = $(SRCS:.c=.o)


# --- Rules ---

# The default rule that is executed when you just type "make".
# It depends on the main target, $(NAME).
all: $(NAME)

# Rule to link all object files into the final executable.
# It depends on all object files. If any .o file is newer than $(NAME),
# this rule will be executed.
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "philo_bonus compiled successfully!"

# Generic rule to compile a .c file into a .o file.
# "%.o" is the target (any file ending in .o)
# "%.c" is the prerequisite (a file with the same name ending in .c)
# It also depends on the header file(s). If a header changes, all source
# files will be recompiled.
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $<"

# Rule to clean up object files.
clean:
	$(RM) $(OBJS)
	@echo "Object files removed."

# Rule to clean up everything (object files + executable).
# It first calls the "clean" rule.
fclean: clean
	$(RM) $(NAME)
	@echo "Executable removed."

# Rule to force a full re-compilation.
# It calls "fclean" first to delete everything, then calls "all" to re-build.
re: fclean all

# --- Phony Targets ---

# Declares targets that are not actual files. This tells "make" to
# always run the commands for these targets, and prevents conflicts if a
# file with the same name (e.g., "clean") exists in the directory.
.PHONY: all clean fclean re