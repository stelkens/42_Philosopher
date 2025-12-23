# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 16:50:14 by tstelken          #+#    #+#              #
#    Updated: 2025/12/23 10:47:48 by tstelken         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = philo
SRC = $(addprefix src/, main.c\
						handle_func.c\
						init.c\
						utils.c\
						dinner.c\
						getter_setter.c\
						philo_actions.c\
						monitor.c\
						more_utils.c\
						)

OBJ := $(SRC:src/%.c=build/%.o)

CFLAGS = -Wall -Wextra -Werror -Iinclude

DFLAG = -g

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) -o $(NAME)

build/%.o: src/%.c include/philo.h
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $<

debug: CFLAGS += $(DFLAG)
debug:	fclean $(NAME)
		@echo "Debug_Build done"

clean:
		rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all