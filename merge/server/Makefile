##
## Makefile for Makefile in /home/merran_g/work/c_igraph/raytracer/merge/server
## 
## Made by Geoffrey Merran
## Login   <merran_g@epitech.net>
## 
## Started on  Sat Jun  7 22:41:08 2014 Geoffrey Merran
## Last update Sat Jun  7 23:02:40 2014 Geoffrey Merran
##

RM		= rm -f

CC		= cc `pkg-config --libs --cflags gtk+-2.0`

CFLAGS		+= -Wextra -Wall -W -pedantic -ansi -g3 -I$(I_PATH)

I_PATH		= ./includes/

NAME		= rt

LIBX11		= /usr/lib64/X11

OBJ		= $(SRC:.c=.o)

D_CORE		= src/core/
D_FUNC		= src/func/

SRC		= $(D_CORE)main.c			\
		$(D_CORE)list.c				\
		$(D_CORE)read_inf.c			\
		$(D_FUNC)get_next_line.c		\
		$(D_FUNC)my_alloc_init.c		\

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lX11 -L$(LIBX11)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
