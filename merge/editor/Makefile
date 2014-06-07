##
## Makefile for  in /home/ades_n/Workspace/gui
## 
## Made by nicolas ades
## Login   <ades_n@epitech.net>
## 
## Started on  Wed Jun  4 13:16:58 2014 nicolas ades
## Last update Sat Jun  7 22:59:42 2014 Geoffrey Merran
##

SRC	=	help.c		\
		main_btn.c	\
		main_btn2.c	\
		main_ins.c	\
		main_ins2.c	\
		main_ins3.c	\
		save.c		\
		main_window.c	\
		editor.c	\
		main.c		\

NAME	=	editor

OBJ	=	$(SRC:.c=.o)

CC	=	gcc `pkg-config --cflags --libs gtk+-2.0`

RM	=	rm -f

CFLAGS	+=	 -W -Wall -Wextra -Werror -ansi -pedantic -I.

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
