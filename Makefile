NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c \
	   set_args.c \
	   actions.c \
	   fork_handler.c \
	   mutex_handler.c \
	   kill.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o philo
	@echo "\033[0;32m[EXECUTABLE CREATED]\033[0"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[0;32m[FILES COMPILED]\033[0"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;31m[CLEARED]\033[0"

re: fclean all

.PHONY: all clean fclean re
