# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 00:21:51 by dlom              #+#    #+#              #
#    Updated: 2024/03/20 20:46:24 by dlom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	redlomshell
SRCS =	redlomshell.c \
		error_handling.c \
		parser/construct.c \
		parser/parsing.c \
		executor/rund_cmd.c\


OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -lreadline

all: lib $(NAME)

lib:
	make -C libft

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJS)
	make fclean -C libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re