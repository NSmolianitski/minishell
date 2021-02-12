/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:06:06 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:06:09 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_utils.h"

static void	is_n_option(int n_option)
{
	if (!n_option)
		write(1, "\n", 1);
}

static void	print_args(char **args, int i)
{
	while (args[i])
	{
		print_line(args[i], 1);
		++i;
		if (!args[i])
			break ;
		if (ms_strcmp(args[i - 1], ""))
			write(1, " ", 1);
	}
}

int			ms_echo(char **args)
{
	int		i;
	int		n_option;

	i = 0;
	n_option = 0;
	if (!args)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ms_strcmp(args[0], "-n"))
	{
		n_option = 1;
		while (!ms_strcmp(args[i], "-n"))
			++i;
	}
	print_args(args, i);
	is_n_option(n_option);
	return (0);
}
