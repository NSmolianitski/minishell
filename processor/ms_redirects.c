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

/*
**  A function that replaces file descriptors for redirects
*/

static void	make_redir(char *file, int stream, t_cmd *cmd, int index)
{
	int		temp_fd;
	char	buff[1000];

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
		dup2(temp_fd, 1);
		rm_redir_out(cmd, index);
	}
	else
	{
		temp_fd = open(file, O_RDWR | O_CREAT, 0666);
		dup2(temp_fd, 0);
		rm_redir_in(cmd, index);
	}
	close(temp_fd);
}

/*
**  A function that handles redirects if they exists
*/

void		handle_redirects(t_cmd *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (!ms_strcmp(">", cmd->args[i]) && ms_strcmp(">", cmd->args[i + 1]))
		{
			make_redir(cmd->args[i + 1], 1, cmd, i);
			i = 0;
		}
		else if (!ms_strcmp("<", cmd->args[i]))
		{
			make_redir(cmd->args[i + 1], 0, cmd, i);
			i = 0;
		}
		else if (!ms_strcmp(">", cmd->args[i]) &&
				!ms_strcmp(">", cmd->args[i + 1]))
		{
			make_redir(cmd->args[i + 2], 3, cmd, i);
			i = 0;
		}
		++i;
	}
}
