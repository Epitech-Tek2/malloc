##
## EPITECH PROJECT, 2021
## my_malloc [WSL: Ubuntu]
## File description:
## Makefile
##

SRCS	=	sources/index.c	\
			sources/malloc.c	\
			sources/realloc.c	\
			sources/free.c

CFLAGS	=	-W -Wall -Wextra -Werror

NAME	=	libmy_malloc.so

all:	$(NAME)

$(NAME):
	gcc -fPIC $(SRCS) -shared -o $(NAME) $(CFLAGS) -Iincludes/

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	rm -f libmy_malloc.so

re: fclean all

run:
	gcc $(SRCS) main.c -o test -lmy_malloc -L. -g -Iincludes/