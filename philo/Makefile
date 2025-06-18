NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE= -g -fsanitize=address
RM = rm -rf

SRC = main.c
OBJ = $(SRC:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJ) -o $(NAME)

%.o:%.c $(INCLUDE) Makefile
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
