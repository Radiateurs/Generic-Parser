CC		= gcc

AR		= ar rcs

CP		= cp

LIBNAME		= libmap.a

TREESRC		= src/tree/element/dump.c	\
		  src/tree/element/getter.c	\
		  src/tree/element/create.c	\
		  src/tree/element/delete.c	\
		  src/tree/segment/dump.c	\
		  src/tree/segment/getter.c	\
		  src/tree/segment/create.c	\
		  src/tree/segment/delete.c	\
		  src/tree/message/dump.c	\
		  src/tree/message/getter.c	\
		  src/tree/message/create.c	\
		  src/tree/message/delete.c

JSONSRC		= src/JSON/serialize.c		\
		  src/JSON/tree_manipulation.c	\
		  src/JSON/state_parser.c	\
		  src/JSON/create_tree.c	\
		  src/JSON/rte_callable.c

XMLSRC		= src/XML/serialize.c		\
		  src/XML/tree_manipulation.c	\
		  src/XML/state_parser.c	\
		  src/XML/token_parse.c		\
		  src/XML/create_tree.c		\
		  src/XML/rte_callable.c

NAVSRC		= src/navigation/access/access_segment.c	\
		  src/navigation/access/access_child.c		\
		  src/navigation/access/access_element.c	\
		  src/navigation/modification/modify_segment.c	\
		  src/navigation/modification/modify_child.c	\
		  src/navigation/modification/modify_element.c	\
		  src/navigation/movement/move_in_segment.c	\
		  src/navigation/movement/move_in_child.c	\
		  src/navigation/movement/move_in_element.c

SRC		= src/string_utils.c		\
		  src/parse.c			\
		  src/JSONparse.c		\
		  src/XMLparse.c		\
		  src/token_parse.c		\
		  src/rte_function.c		\
		  $(TREESRC)			\
		  $(JSONSRC)			\
		  $(XMLSRC)			\
		  $(NAVSRC)

OBJ		= $(SRC:.c=.o)

RM		= rm -rf

CFLAGS		+= -m32 -I./include/ -W -Wall -Werror

all:		$(LIBNAME)

$(LIBNAME):	$(OBJ)
		$(AR) $(LIBNAME) $(OBJ)
		$(CP) $(LIBNAME) ../

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(LIBNAME)

re:		fclean all

dbg:		CFLAGS += -g
dbg:		re

.PHONY:		$(LIBNAME) clean fclean re dbg
