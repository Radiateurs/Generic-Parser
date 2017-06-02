CC		= gcc

NAME		= test

TREESRC		= src/tree/attribut.c		\
		  src/tree/element.c		\
		  src/tree/segment.c		\
		  src/tree/message.c


JSONSRC		= src/JSON/serialize.c		\
		  src/JSON/tree_manipulation.c	\
		  src/JSON/state_parser.c	\
		  src/JSON/create_tree.c

XMLSRC		= src/XML/serialize.c		\
		  src/XML/tree_manipulation.c	\
		  src/XML/state_parser.c	\
		  src/XML/token_parse.c		\
		  src/XML/create_tree.c		

SRC		= src/main.c			\
		  src/string_utils.c		\
		  src/parse.c			\
		  src/JSONparse.c		\
		  src/XMLparse.c		\
		  src/token_parse.c		\
		  $(TREESRC)			\
		  $(JSONSRC)			\
		  $(XMLSRC)

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
