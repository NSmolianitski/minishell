#ifndef MINISHELL_MS_PROCESSOR_H
# define MINISHELL_MS_PROCESSOR_H

#include "ms_parser.h"

int		g_exit_status;
void	processor(t_cmd	**cmd_arr, t_list **env_list);

#endif
