NAME		=	minishell
CC			=	gcc
SRC			=	$(wildcard processor/*.c \
				utils/*.c \
				parser/*.c \
				get_next_line/*.c \
				commands/*.c \
				main.c)

HEADERS		=	includes/get_next_line.h \
				includes/ms_commands.h \
				includes/ms_parser.h \
				includes/ms_processor.h \
				includes/ms_utils.h \
				libft/libft.h

OBJ			=	$(SRC:.c=.o)
FLAGS		=	-Werror -Wextra -Werror
LIBFTDIR	=	libft
LIBFTLIB	=	libft.a
INCL		=	./includes

.PHONY:		all clean fclean re

all:		$(NAME)

%.o:		%.c
			$(CC) $(FLAGS) -I$(INCL) -I$(LIBFTDIR) -c $< -o $@

$(NAME):	$(OBJ) $(HEADERS)
			make -C $(LIBFTDIR)
			make bonus -C $(LIBFTDIR)
			cp $(LIBFTDIR)/$(LIBFTLIB) ./
			$(CC) $(LIBFTLIB) $(FLAGS) $(OBJ) -o $(NAME)

clean:
			rm -f $(OBJ)
			make clean -C $(LIBFTDIR)

fclean:		clean
			rm -f $(NAME)
			rm -f $(LIBFTLIB)
			make fclean -C $(LIBFTDIR)

re:			fclean all