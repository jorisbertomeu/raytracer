SRC	=	help.c		\
		main_btn.c	\
		main_btn2.c	\
		main_ins.c	\
		main_ins2.c	\
		main_ins3.c	\
		push_in_file.c	\
		save.c		\
		main_window.c	\
		editor.c	\
		main.c		\

NAME	=	editor

OBJ	=	$(SRC:.c=.o)

CC	=	gcc `pkg-config --cflags --libs gtk+-2.0` -g3

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
