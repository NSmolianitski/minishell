/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:56:09 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:56:10 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_parser.h"
#include "libft.h"
#include "ms_utils.h"

/*
**  A function that checks command line for emptiness
*/

static int		check_for_empty_line(const char *cmd_line)
{
	int		i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

static void		parse_commands(const char *cmd_line, int i,
						int j, t_cmd **cmd_arr)
{
	while (cmd_line[i] != '\0')
	{
		parse_cmd(cmd_line, &i, cmd_arr[j]);
		++j;
	}
}

static int		check_redirs(const char *cmd_line)
{
	int	i;
	int flag;
	int	quotes;

	i = 0;
	flag = 0;
	quotes = 0;
	while (cmd_line[i])
	{
		check_redir_quotes(&quotes, i, cmd_line);
		if (!quotes)
			check_redir_parser_norm(&flag, cmd_line, &i);
		++i;
	}
	if (flag)
		return (print_redir_err());
	return (0);
}

t_cmd			**parser(const char *cmd_line)
{
	t_cmd	**cmd_arr;
	int		i;
	int		j;
	int		k;

	if (check_redirs(cmd_line))
		return (0);
	i = 0;
	j = check_for_empty_line(cmd_line);
	if (j)
		return (0);
	j = count_cmds(cmd_line);
	if (!j)
		return (0);
	cmd_arr = malloc(sizeof(t_cmd *) * (j + 1));
	k = 0;
	while (k < j)
	{
		cmd_arr[k] = malloc(sizeof(t_cmd));
		++k;
	}
	cmd_arr[j] = NULL;
	j = 0;
	parse_commands(cmd_line, i, j, cmd_arr);
	return (cmd_arr);
}
