# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 01:54:11 by meghribe          #+#    #+#              #
#    Updated: 2025/06/28 11:22:07 by meghribe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread -fsanitize=thread
RM = rm -rf
MKDIR = mkdir -p

SRC_DIR = .
OBJ_DIR = obj
INC_DIR = .

SRCS = main.c utils.c init.c routine.c monitor.c debug.c print.c
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
