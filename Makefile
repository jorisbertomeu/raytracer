##
## Makefile for Makefile in /home/merran_g/work/c_piscine/Piscine-C-Jour_11/do-op
## 
## Made by Geoffrey Merran
## Login   <merran_g@epitech.net>
## 
## Started on  Mon Oct 21 13:28:05 2013 Geoffrey Merran
## Last update Mon Jun  2 09:40:10 2014 Jeremy Mediavilla
##

RM		= rm -f

CC		= cc
CFLAGS		+= -Wextra -Wall -W -pedantic -ansi -g3 -I$(I_PATH)

I_PATH		= ./includes/

NAME		= rtv1

OBJ		= $(SRC:.c=.o)

LIBS		= -lmy -lmymlx -lmlx -lXext -lX11

LIB		= libmy/
LIBMYX		= libmymlx/
LIBX11		= /usr/lib64/X11
LIBXEXT		= /usr/lib64

D_CORE		= src/core/
D_INTER		= src/inter/
D_PARSER	= src/parser/
D_SHAPE		= src/shape/
D_LUM		= src/luminosity/

SRC		= $(D_CORE)main.c			\
		$(D_CORE)hook.c				\
		$(D_INTER)get_simple_pos.c 		\
		$(D_INTER)get_simple_pos2.c		\
		$(D_INTER)find_inter.c			\
		$(D_PARSER)items.c 			\
		$(D_PARSER)list.c 			\
		$(D_PARSER)read_inf.c 			\
		$(D_SHAPE)sphere.c			\
		$(D_SHAPE)plan.c 			\
		$(D_SHAPE)cylinder.c 			\
		$(D_SHAPE)cone.c			\
		$(D_LUM)luminosity.c 			\
		$(D_CORE)xfunction.c			\

all:	libs $(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS) -L$(LIB) -L$(LIBMYX) -L$(LIBX11) -L$(LIBXEXT) -lm

libs:
	make -C $(LIB)
	make -C $(LIBMYX)

clean:
	(cd $(LIB); make clean)
	(cd $(LIBMYX); make clean)
	$(RM) $(OBJ)

fclean:		clean
	(cd $(LIB); make fclean)
	(cd $(LIBMYX); make clean)
	$(RM) $(NAME)

re:		fclean all

.PHONY:	all libs clean fclean re
