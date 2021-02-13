/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmichiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:12:17 by kmichiko          #+#    #+#             */
/*   Updated: 2021/02/13 14:12:20 by kmichiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ms_processor.h"

int			print_redir_err(void)
{
	print_error(SEN, "", 2);
	return (1);
}

void		free_arr(char **tmp)
{
	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
}

void		check_redir_quotes(int *quotes, int i, const char *cmd_line)
{
	if (!*quotes && cmd_line[i] == '\'' && !is_symb_esc(cmd_line, i))
		*quotes = 1;
	else if (!*quotes && cmd_line[i] == '"' && !is_symb_esc(cmd_line, i))
		*quotes = 2;
	else if (*quotes == 1 && cmd_line[i] == '\'')
		*quotes = 0;
	else if (*quotes == 2 && cmd_line[i] == '"' && !is_symb_esc(cmd_line, i))
		*quotes = 0;
}

int			check_redir_parser_norm(int *flag, const char *cmd_line, int *i)
{
	if (cmd_line[*i] == '>' && !*flag)
		*flag = 2;
	else if (cmd_line[*i] == '<' && !*flag)
		*flag = 1;
	else if (*flag && !ft_strchr(" ><", cmd_line[*i]))
		*flag = 0;
	else if (*flag && (cmd_line[*i] == '<' || cmd_line[*i] == '>'))
	{
		print_redir_err();
		return (1);
	}
	if (cmd_line[*i] == '>' && cmd_line[*i + 1] == '>')
	{
		++(*flag);
		++(*i);
	}
	return (0);
}
