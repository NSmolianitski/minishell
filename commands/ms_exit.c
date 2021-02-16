/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:08:49 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:08:51 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ms_processor.h"
#include "libft.h"

static void	exit_norm(char *str)
{
	unsigned char	status;

	status = ft_atoi(str);
	g_exit_status = status;
}

void		ms_exit(t_cmd *cmd)
{
	int				i;

	print_line("exit\n", 1);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[0][i])
		{
			if (!ft_isdigit(cmd->args[0][i]) &&
			!(cmd->args[0][0] == '-' && ft_isdigit(cmd->args[0][1])))
			{
				print_error(NAR, cmd->args[0], 6);
				exit(255);
			}
			else if (cmd->args[1])
			{
				print_error(TMA, NULL, 6);
				g_exit_status = 1;
				return ;
			}
			++i;
		}
		exit_norm(cmd->args[0]);
	}
	exit(g_exit_status);
}
