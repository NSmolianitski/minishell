/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:37:35 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:39:46 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ms_utils.h"
#include "ms_parser.h"
#include "ms_processor.h"

int			redir_in(int *temp_fd, char *file, t_cmd *cmd, int index)
{
	*temp_fd = open(file, O_RDWR);
	if (*temp_fd < 0)
	{
		print_error(NSFD, cmd->args[index + 1], 1);
		g_exit_status = 1;
		free(cmd->cmd);
		cmd->cmd = ft_strdup("");
		return (1);
	}
	else
		dup2(*temp_fd, 0);
	return (0);
}

static int	redir_err(t_cmd *cmd, int stream, int index)
{
	if (cmd->args[index + 1])
		return (0);
	print_error(SEN, "", 2);
	g_exit_status = 258;
	free(cmd->cmd);
	cmd->cmd = ft_strdup("");
	free_strs_arr(&cmd->args);
	cmd->args = NULL;
	if (stream == 3)
		rm_redir_append(cmd, index);
	return (1);
}

/*
**  A function that replaces file descriptors for redirects
*/

static int	make_redir(char *file, int stream, t_cmd *cmd, int index)
{
	int		temp_fd;
	char	buff[1000];

	if (redir_err(cmd, stream, index))
		return (0);
	if (stream == 3)
	{
		temp_fd = open(file, O_RDWR | O_CREAT, 0666);
		while (read(temp_fd, buff, 999))
			;
		dup2(temp_fd, 1);
		rm_redir_append(cmd, index);
	}
	else if (stream == 1)
	{
		temp_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		redir_stream_one(temp_fd, cmd, index);
	}
	else
	{
		if (redir_err_norm(&temp_fd, file, cmd, index))
			return (1);
	}
	close(temp_fd);
	return (0);
}

static int	redir_cycle(t_cmd *cmd, int *i)
{
	int	err;

	err = 0;
	if (!ms_strcmp(">", cmd->args[*i]) && (!cmd->args[*i + 1] ||
				ms_strcmp(">", cmd->args[*i + 1])))
	{
		err = make_redir(cmd->args[*i + 1], 1, cmd, *i);
		*i = 0;
	}
	else if (!ms_strcmp("<", cmd->args[*i]))
	{
		err = make_redir(cmd->args[*i + 1], 0, cmd, *i);
		*i = 0;
	}
	else if (!ms_strcmp(">", cmd->args[*i]) &&
				!ms_strcmp(">", cmd->args[*i + 1]))
	{
		err = make_redir(cmd->args[*i + 2], 3, cmd, *i);
		*i = 0;
	}
	else
		++(*i);
	if (err)
		return (1);
	return (0);
}

/*
**  A function that handles redirects if they exists
*/

void		handle_redirects(t_cmd *cmd)
{
	int	i;

	if (*cmd->cmd == '>' || *cmd->cmd == '<')
	{
		free(cmd->cmd);
		cmd->cmd = ft_strdup("");
		print_error(SEN, "", 2);
		g_exit_status = 258;
		return ;
	}
	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (redir_cycle(cmd, &i))
			return ;
	}
}
