/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:27:56 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/13 17:27:57 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

void		check_bslash(char *tmp, int *i, char **str, int *str_diff)
{
	if (tmp[*i + 1] == '\\')
	{
		ms_strswap(str, "\\", (*i - *str_diff), 1);
		++(*i);
	}
	else
		ms_strswap(str, "", (*i - *str_diff), 0);
	++(*str_diff);
	++(*i);
}

int			check_bslash2(char **str, int i)
{
	if ((*str)[i + 1] == '\\')
	{
		ms_strswap(str, "\\", i, 1);
		return (i);
	}
	else
		ms_strswap(str, "", i, 0);
	return (i);
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

static void	first_arg_check(t_cmd *cmd)
{
	if (!cmd->args[0])
	{
		free(cmd->args);
		cmd->args = NULL;
	}
}

void		check_empty_args(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			if (!ms_strcmp(cmd->args[i], "ENV NO CONTENT!"))
			{
				free(cmd->args[i]);
				while (cmd->args[i + 1])
				{
					cmd->args[i] = ft_strdup(cmd->args[i + 1]);
					free(cmd->args[i + 1]);
					++i;
				}
				cmd->args[i] = NULL;
				i = 0;
			}
			else
				++i;
		}
		first_arg_check(cmd);
	}
}
