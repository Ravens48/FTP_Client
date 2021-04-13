NAME	= myftp

CC		= gcc

RM		= rm -f

SRCS	= src/main.c \
		  src/server.c

OBJS	= $(SRCS:.c=.o)

CFLAGS 	= -I 
CFLAGS 	+= -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
