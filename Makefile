# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 00:21:51 by dlom              #+#    #+#              #
#    Updated: 2024/02/04 00:57:21 by dlom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	redlomshell
SRCS =	redlomshell.c \


OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -pthread -lreadline

all: lib $(NAME)

lib:
	make -C libft

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@	

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re