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

void	ms_exit(t_cmd *cmd)
{
	unsigned char	status;
	int				i;

	print_line("exit\n", 1);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[0][i])
		{
			if (!ft_isdigit(cmd->args[0][i]) && cmd->args[0][0] != '-')
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
		status = ft_atoi(cmd->args[0]);
		g_exit_status = status;
	}
	exit(g_exit_status);
}
