##
## Makefile for Makefile in /home/merran_g/work/c_igraph/raytracer
## 
## Made by Geoffrey Merran
## Login   <merran_g@epitech.net>
## 
## Started on  Tue Jun  3 17:03:02 2014 Geoffrey Merran
## Last update Fri Jun  6 17:26:42 2014 Geoffrey Merran
##

RM		= rm -f

CC		= cc
CFLAGS		+= -Wextra -Wall -W -pedantic -ansi -g3 -I$(I_PATH)

I_PATH		= ./includes/

NAME		= raytracer

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
D_REFL		= src/reflexion/
D_TMP		= src/kekette/

SRC		= $(D_CORE)main.c			\
		$(D_CORE)calc_img.c			\
		$(D_CORE)hook.c				\
		$(D_CORE)utility.c			\
		$(D_INTER)get_simple_pos.c 		\
		$(D_INTER)get_simple_pos2.c		\
		$(D_INTER)find_inter.c			\
		$(D_INTER)get_normal.c			\
		$(D_PARSER)get_effects.c		\
		$(D_PARSER)get_eye.c			\
		$(D_PARSER)get_next_line.c		\
		$(D_PARSER)get_shape.c			\
		$(D_PARSER)get_spot.c			\
		$(D_PARSER)init.c			\
		$(D_PARSER)parser.c			\
		$(D_PARSER)parser2.c			\
		$(D_PARSER)my_alloc_init.c		\
		$(D_PARSER)my_free_wordtab.c		\
		$(D_PARSER)my_xrealloc.c		\
		$(D_PARSER)xclose.c			\
		$(D_PARSER)xfree.c			\
		$(D_PARSER)xopen.c			\
		$(D_SHAPE)sphere.c			\
		$(D_SHAPE)plan.c 			\
		$(D_SHAPE)cylinder.c 			\
		$(D_SHAPE)cone.c			\
		$(D_LUM)luminosity.c 			\
		$(D_LUM)shadow.c 			\
		$(D_REFL)reflexion.c			\
		$(D_CORE)xfunction.c			\
		$(D_TMP)stock_color.c			\

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
