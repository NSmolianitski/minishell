#include "ms_utils.h"
#include "ms_parser.h"

void	ms_unset(t_cmd *cmd, t_list **env_list)
{
	int i;

	i = 0;
	if (!cmd->args)
		return ;
	while (cmd->args[i])
	{
		rm_var(env_list, cmd->args[i]);
		++i;
	}
}