CC	= gcc
LIBC	= ar rc
CFLAGS	+= -Wall -Werror -Wextra
SRC = printf_fd.c \
		mandatory/ft_get_arg.c \
		mandatory/ft_print_hex.c \
		mandatory/ft_print_ptr.c \
		mandatory/ft_printnbr.c \
		mandatory/ft_printuns.c \
		utils/ft_printstr.c \

OBJS	= $(SRC:.c=.o)

NAME	= printf_fd.a

.PHONY: all clean fclean re norma

all: $(NAME)

.c.o:
	@${CC} ${CFLAGS} -I includes -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@ar rcs ${NAME} ${OBJS}

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all