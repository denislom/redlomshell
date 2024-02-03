# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlom <dlom@student.42prague.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 00:21:51 by dlom              #+#    #+#              #
#    Updated: 2024/02/04 00:30:43 by dlom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	redlomshell
SRCS =	redlomshell.c \


OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -pthread -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@	

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re