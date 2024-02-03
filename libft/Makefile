SRCS		=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
				ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
				ft_strjoin.c ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
				ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstdelone.c ft_printf.c ft_print_decimal_number.c \
				ft_print_hexadecimal.c ft_print_pointer.c ft_print_unsigned_decimal.c \
				ft_putstr.c \
				get_next_line.c get_next_line_utils.c
OBJS		=	${SRCS:.c=.o}
NAME		=	libft.a
INCS		=	libft.h
LIBC		=	ar rc
RM			=	rm -f
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

all: ${NAME}

%.o: %.c ${INCS}
	${CC} ${CFLAGS} -c ${SRCS}

$(NAME): ${OBJS}
	${LIBC} ${NAME} ${OBJS}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re bonus

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)