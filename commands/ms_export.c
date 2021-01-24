#include "ms_utils.h"
#include "ms_parser.h"

void	ms_export(t_cmd *cmd, t_list **env_list)
{
	int 	i;
	int 	j;
	int 	k;
	char	*name;
	char	*content;
	t_list	*new_lst;

/*
**	- if there is an A=A variable, then 'export A' command does nothing
**	- replace existing variable or create a new one
 */

	if (!cmd->args)
	{
		print_list(*env_list, 1);
		return ;							//!!!can be deleted, but don't forget to fix segfault!!!
	}
	i = 0;
	k = 0;
	while (cmd->args[k])
	{
		while (cmd->args[k][i] != '=' && cmd->args[k][i] != '\0')
			++i;
		name = ft_substr(cmd->args[k], 0, i);
		if (find_var(*env_list, name))
			print_line("Variable exists\n", 1);
		else
		{
			if (cmd->args[k][i] == '=')
			{
				++i;
				j = i;
				while (cmd->args[0][i] != '\0')
					++i;
				content = ft_substr(cmd->args[k], j, i - j);
			} else
				content = NULL;
			new_lst = ft_lstnew(name, content);
			ft_lstadd_back(env_list, new_lst);
		}
		++k;
	}
}