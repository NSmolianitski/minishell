/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:09:20 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 12:09:22 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_utils.h"
#include "ms_parser.h"

static void	while_gw(const char *cmd_line, int *i)
{
	int quotes_flag;

	quotes_flag = 0;
	while (cmd_line[*i])
	{
		if (!is_symb_esc(cmd_line, *i) &&
			!quotes_flag && ft_strchr("<> |;", cmd_line[*i]))
			break ;
		if ((quotes_flag == 1 && cmd_line[*i] == '\'') ||
			(quotes_flag == 2 && cmd_line[*i] == '"'))
		{
			quotes_flag = 0;
			++(*i);
			continue ;
		}
		if (!quotes_flag && cmd_line[*i] == '\'')
			quotes_flag = 1;
		else if (!quotes_flag && cmd_line[*i] == '"')
			quotes_flag = 2;
		++(*i);
	}
}

/*
**  A function that gets word from command line
*/

int			get_word(const char *cmd_line, char **cmd, int i)
{
	int start;

	start = i;
	if (ft_strchr("<>", cmd_line[i]) && !is_symb_esc(cmd_line, i))
	{
		++i;
		*cmd = ft_substr(cmd_line, start, i - start);
		return (i);
	}
	while_gw(cmd_line, &i);
	*cmd = ft_substr(cmd_line, start, i - start);
	return (i);
}

/*
**  A function that counts arguments from command line
*/

int			count_args(const char *cmd_line, int i)
{
	int		args_num;

	args_num = 1;
	while (cmd_line[i] != '\0' && cmd_line[i] != ';' && cmd_line[i] != '|')
	{
		if (cmd_line[i] == ' ' || (ft_strchr("<>", cmd_line[i]) &&
			!is_symb_esc(cmd_line, i)))
		{
			i = skip_spaces(cmd_line, i);
			if (ft_strchr("<>", cmd_line[i]))
				if (!ft_strchr(";\0|", cmd_line[i]))
					++args_num;
			++args_num;
		}
		++i;
	}
	return (args_num);
}

/*
**  A function that creates an array with arguments
*/

int			get_args(const char *cmd_line, char ***args, int i)
{
	int		arg_index;

	arg_index = 0;
	*args = malloc(sizeof(char *) * (count_args(cmd_line, i) + 1));
	while (cmd_line[i] != '\0' && cmd_line[i] != ';' && cmd_line[i] != '|')
	{
		i = skip_spaces(cmd_line, i);
		i = get_word(cmd_line, &(*args)[arg_index], i);
		i = skip_spaces(cmd_line, i);
		++arg_index;
	}
	(*args)[arg_index] = 0;
	return (i);
}

/*
**  A function that creates command structure for one command
*/

void		parse_cmd(const char *cmd_line, int *i, t_cmd *cmd)
{
	*i = skip_spaces(cmd_line, *i);
	*i = get_word(cmd_line, &cmd->cmd, *i);
	*i = skip_spaces(cmd_line, *i);
	if (!(cmd_line[*i] == '\0' || cmd_line[*i] == ';' || cmd_line[*i] == '|'))
		*i = get_args(cmd_line, &cmd->args, *i);
	else
		cmd->args = NULL;
	cmd->end = cmd_line[*i];
	if (cmd_line[*i] != '\0')
		++(*i);
	*i = skip_spaces(cmd_line, *i);
}
