/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:34:21 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 14:34:23 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

static int	rri_norm(int *i, t_cmd *cmd)
{
	*i = 0;
	while (cmd->args[*i])
		++(*i);
	if (*i == 3 && cmd->args[0][0] == '>')
	{
		free(cmd->args[0]);
		free(cmd->args[1]);
		free(cmd->args[2]);
		free(cmd->args);
		cmd->args = NULL;
		return (0);
	}
	return (1);
}

static void	rri_norm2(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

static void	rri_norm3(int i, t_cmd *cmd)
{
	free(cmd->args[i]);
	free(cmd->args[i + 1]);
	free(cmd->args[i + 2]);
}

/*
**  A function that removes unnecessary '>>' redirect and file name
*/

void		rm_redir_append(t_cmd *cmd, int index)
{
	int		i;
	int		j;
	char	**new_args;

	if (!rri_norm(&i, cmd))
		return ;
	new_args = malloc(sizeof(char *) * (i - 2));
	rri_norm2(&i, &j);
	while (cmd->args[i])
	{
		if (i == index)
		{
			rri_norm3(i, cmd);
			i += 3;
			continue ;
		}
		new_args[j] = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		++i;
		++j;
	}
	new_args[j] = 0;
	free(cmd->args);
	cmd->args = new_args;
}

void		redir_stream_one(int temp_fd, t_cmd *cmd, int index)
{
	dup2(temp_fd, 1);
	rm_redir_out(cmd, index);
}
