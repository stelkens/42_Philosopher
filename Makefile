# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tstelken <tstelken@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/10 16:50:14 by tstelken          #+#    #+#              #
#    Updated: 2025/12/10 17:36:06 by tstelken         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = philo
SRC = $(addprefix src/, main.c\
						init.c\
						utils.c\
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