#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

void	ms_unset(t_cmd *cmd, t_list **env_list)
{
	int i;

	i = 0;
	if (!cmd->args)
		return ;
	while (cmd->args[i])
	{
		if (ft_isdigit(cmd->args[i][0]))
		{
			print_error(NVI, cmd->args[i], 7);
			g_exit_status = 1;
			return ;
		}
		rm_var(env_list, cmd->args[i]);
		++i;
	}
}