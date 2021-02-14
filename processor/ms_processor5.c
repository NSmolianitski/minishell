/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:24:37 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 13:24:39 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

static void	sq_norm3(t_cmd *cmd, t_list *env_list, char **str, int is_cmd)
{
	swap_env(str, env_list);
	if (is_cmd)
		check_multiword_env(cmd);
}

/*
**  A function that gets coordinates of quotes string and parses that string
*/

int			swap_quotes(char **str, t_list *env_list, t_cmd *cmd, int is_cmd)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	tmp = NULL;
	g_echo = 0;
	if (!is_cmd)
		g_echo = 1;
	if (ms_bs_strchr(*str, '\'') || ms_bs_strchr(*str, '"'))
	{
		ret = sq_norm6(i, str, env_list, tmp);
		if (ret == 1)
			return (1);
		else if (ret == 0)
			return (0);
	}
	else
	{
		handle_bslash(str);
		sq_norm3(cmd, env_list, str, is_cmd);
	}
	return (0);
}

int			echo_empty_check(char **str)
{
	if (g_echo)
	{
		if (!ms_strcmp(*str, "''") || !ms_strcmp(*str, "\"\""))
		{
			*str = ft_strdup("echos empty argument :D");
			return (1);
		}
	}
	return (0);
}