# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 19:43:07 by meghribe          #+#    #+#              #
#    Updated: 2025/07/03 17:29:48 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread -fsanitize=thread
RM = rm -rf
MKDIR = mkdir -p

SRC_DIR = .
INC_DIR = .
OBJ_DIR = obj

SRCS = routine.c state.c init.c main.c monitor.c parsing.c \
	threadsafe.c sync.c utils.c print.c
HEADER = $(INC_DIR)/philo.h

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(HEADER) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
