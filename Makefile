NAME = philo

ARGS  = 5 800  200 200
ARGS2  = 1 800 200 200 

# Source files
SRC = src/main.c src/ft_atoi.c src/actions.c src/init.c src/monitor.c src/threads.c \
		src/utils.c src/cleanup.c
		
# Object files
OBJ =$(SRC:.c=.o)

# Dependency files
DEP = $(OBJ:.o=.d)

# Include .d files only if they exists ignore otherwise
-include $(DEP)

# Compiler and Flags(-MMD generate dependency files to update if .h files are updated -MP prevents errors for .h)
CC = cc
INCLUDE = -I./include/
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3 -pthread $(INCLUDE)

# sets default target
.DEFAULT_GOAL := all

# build the target $(NAMES)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✓ built $(NAME)"

#run with args
run: $(NAME)
	./$(NAME) $(ARGS)

run2: $(NAME)
	./$(NAME) $(ARGS2)

#run with valgrind and run with args
testv: $(NAME)
	-valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS)
	-valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS2)

testh: $(NAME)
	-valgrind --tool=helgrind ./$(NAME) $(ARGS)
	-valgrind --tool=helgrind ./$(NAME) $(ARGS2)

testd: $(NAME)
	-valgrind --tool=drd ./$(NAME) $(ARGS)
	-valgrind --tool=drd ./$(NAME) $(ARGS2)

#run with fsantiser and run with args in test_CMD
testfs: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address -g" all
	./$(NAME) $(ARGS)

testfs2: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address -g" all
	./$(NAME) $(ARGS2)
	
# Compile .c files to .o files and generate dependency files
src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Remove object and dependency files
clean:
	rm -f $(OBJ) $(DEP)

# Remove program
fclean: clean
	rm -f $(NAME) 
	
# Delete everything and rebuilt from scratch
re: fclean all

# Phony targets (commands and not files)
.PHONY: all clean fclean re testv testfs testh testd run run2 testfs2

