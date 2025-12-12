NAME = philo

# Source files
SRC = src/utils_ft_atof.c src/events.c src/main.c src/complex_math.c \
		src/too_complex_fractals.c src/initialise_and_exit.c
		
# Object files
OBJ =$(SRC:.c=.o)

# Dependency files
DEP = $(OBJ:.o=.d)

# Include .d files only if they exists ignore otherwise
-include $(ALL_DEP)

# Compiler and Flags(-MMD generate dependency files to update if .h files are updated -MP prevents errors for .h)
CC = cc
INCLUDE = -I./include/
CFLAGS = -Wall -Wextra -Werror -MMD -MP $(INCLUDE)

# sets default target
.DEFAULT_GOAL := all

# build the target $(NAMES)
all: $(NAME)

$(NAME):
	    $(CC) $(OBJ) -o $(NAME)
	    @echo "creating philo"

# Compile .c files to .o files and generate dependency files
src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Remove object and dependency files
clean:
	@echo "cleaning philo .o and .d files"
	@rm -f $(OBJ) $(DEP)

# Remove program
fclean: clean
	@echo "removing philo"
	@rm -f $(NAME) 
	
# Delete everything and rebuilt from scratch
re: fclean all

# Phony targets (commands and not files)
.PHONY: all clean fclean re

