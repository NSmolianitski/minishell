/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:55:16 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 13:55:18 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"
#include "ms_commands.h"

/*
**  A function that removes alone '\' and handles '\\' into '\'
*/

void		handle_bslash(char **str)
{
	char	*tmp;
	int		i;
	int		str_diff;

	tmp = ft_strdup(*str);
	i = 0;
	str_diff = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\\')
		{
			if (tmp[i + 1] == '\\')
			{
				ms_strswap(str, "\\", (i - str_diff), 1);
				++i;
			}
			else
				ms_strswap(str, "", (i - str_diff), 0);
			++str_diff;
			++i;
		}
		++i;
	}
	free(tmp);
}

/*
**  A function that checks for quotes and replace them
*/

int			check_quotes(t_cmd *cmd, t_list *env_list)
{
	int			i;

	if (swap_quotes(&cmd->cmd, env_list, cmd, 1))
		return (1);
	handle_bslash(&cmd->cmd);
	if (!cmd->args)
		return (0);
	i = 0;
	while (cmd->args[i])
	{
		swap_env(&cmd->args[i], env_list);
		if (swap_quotes(&cmd->args[i], env_list, cmd, 0))
			return (1);
		handle_bslash(&cmd->args[i]);
		++i;
	}
	return (0);
}

/*
**  A function that saves and restores in and out file descriptors
*/

void		save_restore_fds(int *in, int *out, int flag)
{
	if (flag)
	{
		*in = dup(0);
		*out = dup(1);
	}
	else
	{
		dup2(*in, 0);
		dup2(*out, 1);
		close(*in);
		close(*out);
	}
}

/*
**  A function that checks what command to execute
*/

int			check_cmd(t_cmd *cmd, t_list **env_list)
{
	int	in;
	int	out;

	save_restore_fds(&in, &out, 1);
	g_exit_status = 0;
	handle_redirects(cmd);
	if (!ms_strcmp(cmd->cmd, "echo"))
		g_exit_status = ms_echo(cmd->args);
	else if (!ms_strcmp(cmd->cmd, "cd"))
		g_exit_status = ms_cd(cmd->args, *env_list);
	else if (!ms_strcmp(cmd->cmd, "pwd"))
		g_exit_status = print_pwd();
	else if (!ms_strcmp(cmd->cmd, "export"))
		ms_export(cmd, env_list);
	else if (!ms_strcmp(cmd->cmd, "unset"))
		ms_unset(cmd, env_list);
	else if (!ms_strcmp(cmd->cmd, "env"))
		ms_env(*env_list);
	else if (!ms_strcmp(cmd->cmd, "exit"))
		ms_exit(cmd);
	else if (!try_external_cmd(cmd, env_list))
		return (0);
	save_restore_fds(&in, &out, 0);
	return (1);
}

/*
**  A function that executes command
*/

void		execute_cmd(t_cmd *cmd, t_list **env_list)
{
	if (check_quotes(cmd, *env_list))
	{
		print_error(MLA, "MULTILINE", 5);
		g_exit_status = 1;
	}
	else if (!check_cmd(cmd, env_list) && ms_strcmp(cmd->cmd, ""))
	{
		print_error(CNF, cmd->cmd, 1);
		g_exit_status = 127;
	}
}
