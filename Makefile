##
## EPITECH PROJECT, 2021
## myFtp
## File description:
## Makefile
##

NAME	= myftp

CC		= gcc

RM		= rm -f

SRCS	= src/main.c \
		  src/helper.c \
		  src/checking_function.c \
		  src/parsing_gesture.c	\
		  src/free_my_homies.c \
		  src/command/function_pointeur.c \
		  src/command/function_pointeur_second.c \
		  src/command/directory.c \
		  src/server.c

OBJS	= $(SRCS:.c=.o)

CFLAGS 	= -I 
CFLAGS 	+= -Wall -Wextra -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
