CC		= gcc

NAME		= test

SRC		= src/main.c			\
		  src/string_utils.c		\
		  src/XMLparse.c		\
		  src/serialize.c		\
		  src/tree_manipulation.c	\
		  src/state_parser.c		\
		  src/token_parse.c		\
		  src/create_tree.c		\
		  src/attribut.c		\
		  src/element.c			\
		  src/segment.c			\
		  src/message.c

OBJ		= $(SRC:.c=.o)

RM		= rm -rf

CFLAGS		+= -I./include/ -W -Wall -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

dbg:		CFLAGS += -g
dbg:		re

.PHONY:		$(NAME) clean fclean re dbg
