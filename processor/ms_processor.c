#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_commands.h"

static int	check_cmd(t_cmd *cmd)
{
	if (!ms_strcmp(cmd->cmd, "echo"))
		ms_echo(cmd->args);
	else if (!ms_strcmp(cmd->cmd, "cd"))
		return (2);
	else if (!ms_strcmp(cmd->cmd, "pwd"))
		return (3);
	else if (!ms_strcmp(cmd->cmd, "export"))
		return (4);
	else if (!ms_strcmp(cmd->cmd, "unset"))
		return (5);
	else if (!ms_strcmp(cmd->cmd, "env"))
		return (6);
	else if (!ms_strcmp(cmd->cmd, "exit"))
		return (7);
	return (0);
}

void		processor(t_cmd	**cmd_arr)
{
	int 	i;

	i = 0;
	while (cmd_arr[i])
	{
		if (!check_cmd(cmd_arr[i]))
			print_error(CNF, cmd_arr[i]->cmd, 1);
		++i;
	}
}
