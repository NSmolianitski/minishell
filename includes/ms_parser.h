#ifndef MINISHELL_MS_PARSER_H
# define MINISHELL_MS_PARSER_H

#include "ms_utils.h"

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	char	end;
}				t_cmd;

t_cmd	**parser(const char *cmd_line, t_list *env_list);
void	swap_env(char **cmd, t_list *env_list);

# endif
