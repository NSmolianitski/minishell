#ifndef MINISHELL_MS_PARSER_H
# define MINISHELL_MS_PARSER_H

typedef struct	s_cmd
{
	char	*cmd;
	char	**args;
	char	end;
}				t_cmd;

t_cmd	**parser(char *cmd_line);

# endif
