NAME		=	minishell
CC			=	gcc
SRC			=	commands/ms_cd.c commands/ms_echo.c commands/ms_env.c commands/ms_exit.c commands/ms_export.c commands/ms_pwd.c commands/ms_unset.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlast.c \
                libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_lstsize.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c parser/ms_parser.c parser/ms_parser2.c parser/ms_parser3.c parser/ms_parser4.c parser/ms_parser_utils.c parser/ms_quotes.c parser/ms_quotes_utils.c processor/ms_checkpath.c processor/ms_processor.c processor/ms_processor2.c processor/ms_processor3.c processor/ms_processor4.c processor/ms_processor5.c processor/ms_processor6.c processor/ms_processor7.c processor/ms_processor8.c processor/ms_redirects.c processor/ms_redirects2.c processor/ms_redirects3.c processor/ms_redirects4.c processor/ms_signal.c utils/ms_errors.c utils/ms_errors_begins.c utils/ms_list_utils.c utils/ms_split.c utils/ms_utils.c utils/ms_utils2.c utils/ms_utils3.c main.c

HEADERS		=	includes/get_next_line.h includes/ms_commands.h includes/ms_parser.h includes/ms_processor.h includes/ms_utils.h libft/libft.h

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