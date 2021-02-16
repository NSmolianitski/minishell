/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:49:58 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 12:49:59 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

/*
**  A function that creates an array of strings from list
*/

void			list_to_arr(t_list *env_list, char ***envp)
{
	int		i;
	char	*tmp;

	i = ft_lstsize(env_list);
	*envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env_list)
	{
		(*envp)[i] = ft_strjoin(env_list->name, "=");
		tmp = (*envp)[i];
		if (!env_list->content)
			(*envp)[i] = ft_strjoin((*envp)[i], "");
		else
			(*envp)[i] = ft_strjoin((*envp)[i], env_list->content);
		free(tmp);
		env_list = env_list->next;
		++i;
	}
	(*envp)[i] = 0;
}

/*
**  A function that makes a new arr with command name in args[0]
*/

void			prepare_args(t_cmd *cmd, char ***args)
{
	int	i;

	if (!cmd->args)
	{
		*args = malloc(sizeof(char *) * 2);
		(*args)[0] = ft_strdup(cmd->cmd);
		(*args)[1] = 0;
		return ;
	}
	i = 0;
	while (cmd->args[i])
		++i;
	*args = malloc(sizeof(char *) * (i + 2));
	(*args)[0] = ft_strdup(cmd->cmd);
	i = 0;
	while (cmd->args[i])
	{
		(*args)[i + 1] = ft_strdup(cmd->args[i]);
		++i;
	}
	(*args)[i + 1] = 0;
}

/*
**  A function that clears an array of strings
*/

void			free_strs_arr(char ***args)
{
	int i;

	i = 0;
	while ((*args)[i])
	{
		free((*args)[i]);
		++i;
	}
	free(*args);
}

static int		free_and_set_status(char **envp, char **args, int status)
{
	free_strs_arr(&envp);
	free_strs_arr(&args);
	status = WEXITSTATUS(status);
	if (status == 255)
		return (0);
	else if (status > 0)
		g_exit_status = status;
	return (1);
}

/*
**  A function that tries to execute external command
*/

int				try_external_cmd(t_cmd *cmd, t_list **env_list)
{
	int		status;
	char	**envp;
	char	**args;
	pid_t	pid;

	list_to_arr(*env_list, &envp);
	prepare_args(cmd, &args);
	pid = fork();
	if (pid == -1)
	{
		print_line("Failed to create child process :(\n", 1);
		return (0);
	}
	if (!pid)
		exit(execve(get_path(cmd->cmd, env_list), args, envp));
	else
	{
		g_signal_flag = -1;
		wait(&status);
	}
	if (!free_and_set_status(envp, args, status))
		return (0);
	return (1);
}
