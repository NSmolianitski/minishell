#include "ms_utils.h"
#include "ms_parser.h"

/*
** 0 -> no such command
** 1 -> echo
** 2 -> cd
** 3 -> pwd
** 4 -> export
** 5 -> unset
** 6 -> env
** 7 -> exit
*/

static int	check_cmd(char *cmd)
{
	if (!ms_strcmp(cmd, "echo"))
		return (1);
	else if (!ms_strcmp(cmd, "cd"))
		return (2);
	else if (!ms_strcmp(cmd, "pwd"))
		return (3);
	else if (!ms_strcmp(cmd, "export"))
		return (4);
	else if (!ms_strcmp(cmd, "unset"))
		return (5);
	else if (!ms_strcmp(cmd, "env"))
		return (6);
	else if (!ms_strcmp(cmd, "exit"))
		return (7);
	else
		return (0);
}

void		processor(t_cmd	**cmd_arr)
{
	int 	i;

	i = 0;
	while (cmd_arr[i])
	{
		if (!check_cmd(cmd_arr[i]->cmd))
			print_error(CNF, cmd_arr[i]->cmd, 1);
		else
			print_line("hello world\n", 1);
		++i;
	}
}
