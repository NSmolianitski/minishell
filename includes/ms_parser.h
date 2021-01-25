#ifndef MINISHELL_MS_PARSER_H
# define MINISHELL_MS_PARSER_H

# include "libft.h"

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	char	end;
}				t_cmd;

t_cmd	**parser(const char *cmd_line);
char *parse_qoutes(char *str, t_list *env_list);

# endif
