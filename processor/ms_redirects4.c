/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:28:35 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 14:28:48 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

static int	rri_norm(int *i, t_cmd *cmd)
{
	*i = 0;
	while (cmd->args[*i])
		++(*i);
	if (*i == 2 && cmd->args[0][0] == '>')
	{
		free(cmd->args[0]);
		free(cmd->args[1]);
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
}

/*
**  A function that removes unnecessary '>' redirect and file name
*/

void		rm_redir_out(t_cmd *cmd, int index)
{
	int		i;
	int		j;
	char	**new_args;

	if (!rri_norm(&i, cmd))
		return ;
	new_args = malloc(sizeof(char *) * (i - 1));
	rri_norm2(&i, &j);
	while (cmd->args[i])
	{
		if (i == index)
		{
			rri_norm3(i, cmd);
			i += 2;
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
