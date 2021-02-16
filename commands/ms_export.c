/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:09:25 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:29:18 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

static void	replace_var(t_cmd *cmd, t_list **env_list, char *name, int index)
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

static void	export_err(char *str)
{
	if (str[0] == '\0')
		print_error(NVI, "=", 3);
	else
		print_error(NVI, str, 3);
	g_exit_status = 1;
	free(str);
}

static int	is_valid_name(char *name)
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

static void	if_find_var(t_cmd *cmd, t_list **env_list, char *name, int arr[2])
{
	int		j;
	char	*content;
	t_list	*new_lst;

	if (find_var(*env_list, name))
		replace_var(cmd, env_list, name, arr[1]);
	else
	{
		if (cmd->args[arr[1]][arr[0]] == '=')
		{
			++arr[0];
			j = arr[0];
			while (cmd->args[arr[1]][arr[0]] != '\0')
				++arr[0];
			content = ft_substr(cmd->args[arr[1]], j, arr[0] - j);
		}
		else
			content = NULL;
		new_lst = ft_lstnew(name, content);
		ft_lstadd_back(env_list, new_lst);
	}
}

void		ms_export(t_cmd *cmd, t_list **env_list)
{
	char	*name;
	int		arr[2];

	if (!cmd->args)
	{
		print_list(*env_list, 1);
		return ;
	}
	arr[1] = 0;
	while (cmd->args[arr[1]])
	{
		arr[0] = 0;
		while (cmd->args[arr[1]][arr[0]] !=
				'=' && cmd->args[arr[1]][arr[0]] != '\0')
			++arr[0];
		name = ft_substr(cmd->args[arr[1]], 0, arr[0]);
		if (!is_valid_name(name))
		{
			++arr[1];
			continue;
		}
		if_find_var(cmd, env_list, name, arr);
		g_exit_status = 0;
		++arr[1];
	}
}
