# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 07:21:18 by mmoussou          #+#    #+#              #
#    Updated: 2024/08/19 08:47:29 by mmoussou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash

CC = gcc

CFLAGS = -pthread -g #-Wall -Werror -Wextra

INCLUDE = ./include

NAME = philo

#find -type f -name "*.c" | sed "s/\.\///g" | xargs -Iname echo "`printf '\t\t\t'`" name "\\"
SRCS = $(shell find src -name '*.c')

OBJS_DIR = obj/

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))


all: $(NAME) clean

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(@D)
	@printf "\x1B[2K\r \x1B[1;32m[ 󱌣 ]\x1B[0m compiling objects... : $<"
	@$(CC) $(CFLAGS) -I$(INCLUDE) $< -c -o $@

$(NAME): $(OBJS)
	@printf "\x1B[2K\r \x1B[1;32m[ 󱌣 ]\x1B[0m objects compiled."
	@printf "\n \x1B[1;33m[ 󱉟 ]\x1B[0m compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDE) -o $(NAME)
	@printf "\x1B[2K\r \x1B[1;33m[ 󱉟 ]\x1B[0m $(NAME) compiled.\n"

clean:
	@rm -rf $(OBJS_DIR)
	@printf " \x1B[1;31m[  ]\x1B[0m deleted objects.\n"

fclean: clean
	@rm -f $(NAME)
	@printf " \x1B[1;31m[  ]\x1B[0m deleted $(NAME).\n"

re: fclean all

.PHONY: all clean fclean re
