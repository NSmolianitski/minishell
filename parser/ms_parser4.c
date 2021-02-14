/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:25:02 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 12:25:03 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"

void			count_cmds_err_check(const char *cmd_line, int i)
{
	if (cmd_line[i] == ';')
		print_error(SES, "", 2);
	else if (cmd_line[i] == '|')
		print_error(SEP, "", 2);
	else
		print_line("look into count_cmds_err_check for answer", 1);
}

static int		end_check(const char *cmd_line, int *i, int *bf, char *cmd)
{
	*i = skip_spaces(cmd_line, *i);
	if (cmd_line[*i] == ';' || cmd_line[*i] == '|')
	{
		if (!cmd || cmd_line[(skip_spaces(cmd_line, *i + 1))] == '\0')
		{
			count_cmds_err_check(cmd_line, *i);
			if (cmd != NULL)
			{
				free(cmd);
				cmd = NULL;
			}
			return (0);
		}
		++(*i);
		*bf = 0;
	}
	if (cmd != NULL)
	{
		free(cmd);
		cmd = NULL;
	}
	return (1);
}

int				count_cmds(const char *cmd_line)
{
	int		i;
	int		cmds_num;
	char	*cmd;
	int		break_flag;

	i = 0;
	cmds_num = 0;
	break_flag = 0;
	while (cmd_line[i])
	{
		cmd = NULL;
		i = skip_spaces(cmd_line, i);
		if (!ft_strchr(" |;", cmd_line[i]))
		{
			i = get_word(cmd_line, &cmd, i);
			if (!break_flag)
				++cmds_num;
			break_flag = 1;
		}
		if (!end_check(cmd_line, &i, &break_flag, cmd))
			return (0);
	}
	return (cmds_num);
}
