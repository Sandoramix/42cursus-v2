NAME=libftprintf.a

CC=clang

CFLAGS=-Wall -Wextra -Werror -I.
CFLAGS+=-g

SRC = ./ft_core.c \
	./ft_printf.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^
	@echo "Library created"

clean:
	rm -f $(OBJ)
	@echo "Objects removed"

fclean: clean
	rm -f $(NAME)
	@echo "Library removed"

re: fclean all
.SILENT:
.PHONY: all clean fclean re