#ifndef MINISHELL_MS_PARSER_H
# define MINISHELL_MS_PARSER_H

#include "ms_utils.h"
# include "libft.h"

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	char	end;
}				t_cmd;

t_cmd	**parser(const char *cmd_line, t_list *env_list);
void	swap_env(char **cmd, t_list *env_list);
char	*parse_qoutes(char *str, t_list *env_list);
char	*ms_strmultichr(const char *s, const char *symbols);

# endif
