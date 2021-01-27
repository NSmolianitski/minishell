#ifndef MINISHELL_MS_PROCESSOR_H
# define MINISHELL_MS_PROCESSOR_H

#include "ms_parser.h"

typedef struct	s_coords
{
	int			start;
	int			end;
	int 		type;
}				t_coords;

int		g_exit_status;
void	processor(t_cmd	**cmd_arr, t_list **env_list);

#endif
