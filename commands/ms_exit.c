#include <stdlib.h>
#include "ms_processor.h"
#include "libft.h"

void ms_exit(t_cmd *cmd)
{
	unsigned char	status;
	int 			i;

	print_line("exit\n", 1);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[0][i])
		{
			if (!ft_isdigit(cmd->args[0][i]))
			{
				print_error(NAR, cmd->args[0], 6);
				exit(255);
			}
			++i;
		}
		status = ft_atoi(cmd->args[0]);
		g_exit_status = status;
	}
	exit(g_exit_status);
}