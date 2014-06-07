RM		= rm -f

CC		= cc `pkg-config --libs --cflags gtk+-2.0`

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
		$(D_CORE)list.c				\
		$(D_CORE)read_inf.c				\
		$(D_INTER)get_simple_pos.c 		\
		$(D_INTER)get_simple_pos2.c		\
		$(D_INTER)find_inter.c			\
		$(D_PARSER)items.c 			\
		$(D_SHAPE)sphere.c			\
		$(D_SHAPE)plan.c 			\
		$(D_SHAPE)cylinder.c 			\
		$(D_SHAPE)cone.c			\
		$(D_LUM)luminosity.c 			\
		$(D_CORE)xfunction.c			\
		get_next_line.c				\
		my_alloc_init.c				\

all:	libs $(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -I./minilibx $(LIBS) -L./minilibx -L$(LIB) -L$(LIBMYX) -L$(LIBX11) -L$(LIBXEXT) -lm

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
