/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:37:28 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:37:29 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

static void		child_checks(int i, int fd[2], int old_fd[2], int pipes_num)
{
	if (i)
	{
		dup2(old_fd[0], 0);
		close(old_fd[0]);
		close(old_fd[1]);
	}
	if (i != pipes_num)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
}

static int		if_parent(int i, int (*old_fd)[2], int fd[2], int pipes_num)
{
	int status;

	if (i)
	{
		close((*old_fd)[0]);
		close((*old_fd)[1]);
	}
	if (i != pipes_num)
	{
		(*old_fd)[0] = fd[0];
		(*old_fd)[1] = fd[1];
	}
	wait(&status);
	return (WEXITSTATUS(status));
}

/*
**  Functions that handles pipes
*/

static void		handle_pipes(t_cmd **cmd_arr, t_list **env_list,
						int pipes_num, int index)
{
	int i;
	int pid;
	int fd[2];
	int old_fd[2];

	i = 0;
	while (i <= pipes_num)
	{
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			child_checks(i, fd, old_fd, pipes_num);
			execute_cmd(cmd_arr[index + i], env_list);
			exit(g_exit_status);
		}
		else
			g_exit_status = if_parent(i, &old_fd, fd, pipes_num);
		++i;
	}
	close(old_fd[0]);
	close(old_fd[1]);
}

/*
**  Functions in processor executes sequently (pipe commands execute together)
*/

void			processor(t_cmd **cmd_arr, t_list **env_list)
{
	int		i;
	int		pipes_num;

	i = 0;
	while (cmd_arr[i])
	{
		if (cmd_arr[i]->end == '|')
		{
			pipes_num = i;
			while (cmd_arr[pipes_num]->end == '|')
				++pipes_num;
			pipes_num -= i;
			handle_pipes(cmd_arr, env_list, pipes_num, i);
			i += pipes_num;
		}
		else
			execute_cmd(cmd_arr[i], env_list);
		++i;
	}
}
