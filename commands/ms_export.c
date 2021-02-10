#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

static void replace_var(t_cmd *cmd, t_list **env_list, char *name, int index)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	while (cmd->args[index][i] != '=' && cmd->args[index][i] != '\0')
		++i;
	if (cmd->args[index][i] == '=' && cmd->args[index][i + 1] == '\0')
	{
		content = ft_strdup("");
		change_var_content(*env_list, name, content);
	}
	else if (cmd->args[index][i] == '=')
	{
		++i;
		j = i;
		while (cmd->args[index][j] != '\0')
			++j;
		content = ft_substr(cmd->args[index], i, j - i);
		change_var_content(*env_list, name, content);
	}
	free(name);
}

static void export_err(char *str)
{
	if (str[0] == '\0')
		print_error(NVI, "=", 3);
	else
		print_error(NVI, str, 3);
	g_exit_status = 1;
	free(str);
}

static int is_valid_name(char *name)
{
	int i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		export_err(name);
		return (0);
	}
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			export_err(name);
			return (0);
		}
		++i;
	}
	return (1);
}

void	ms_export(t_cmd *cmd, t_list **env_list)
{
	int 	i;
	int 	j;
	int 	k;
	char	*name;
	char	*content;
	t_list	*new_lst;

	if (!cmd->args)
	{
		print_list(*env_list, 1);
		return ;
	}
	k = 0;
	while (cmd->args[k])
	{
		i = 0;
		while (cmd->args[k][i] != '=' && cmd->args[k][i] != '\0')
			++i;
		name = ft_substr(cmd->args[k], 0, i);
		if (!is_valid_name(name))
		{
			++k;
			continue;
		}
		if (find_var(*env_list, name))
			replace_var(cmd, env_list, name, k);
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
		g_exit_status = 0;
		++k;
	}
}