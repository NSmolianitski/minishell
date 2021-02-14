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
	int		q_flag;

	tmp = ft_strdup(*str);
	i = 0;
	str_diff = 0;
	q_flag = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'' && !q_flag)
			q_flag = 1;
		else if (tmp[i] == '"' && !q_flag)
			q_flag = 2;
		else if ((tmp[i] == '\'' && q_flag == 1) ||
		(tmp[i] == '"' && q_flag == 2))
			q_flag = 0;
		if (!q_flag && tmp[i] == '\\')
			check_bslash(tmp, &i, str, &str_diff);
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
	if (!cmd->args)
		return (0);
	i = 0;
	while (cmd->args[i])
	{
		swap_env(&cmd->args[i], env_list);
		if (ms_strcmp("echo", cmd->cmd))
		{
			free(cmd->args[i]);
			cmd->args[i] = ft_strdup("");
		}
		if (swap_quotes(&cmd->args[i], env_list, cmd, 0))
			return (1);
		++i;
	}
	return (0);
}

static void	fds_redirs(int *in, int *out, t_cmd *cmd)
{
	save_restore_fds(in, out, 1);
	g_exit_status = 0;
	handle_redirects(cmd);
}

/*
**  A function that checks what command to execute
*/

int			check_cmd(t_cmd *cmd, t_list **env_list)
{
	int	in;
	int	out;

	fds_redirs(&in, &out, cmd);
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
	{
		save_restore_fds(&in, &out, 0);
		return (0);
	}
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
	else if (!check_cmd(cmd, env_list) || !ms_strcmp(cmd->cmd, ""))
	{
		print_error(CNF, cmd->cmd, 1);
		g_exit_status = 127;
	}
}
