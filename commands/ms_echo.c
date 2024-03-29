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

static int	args_check(char **args, int i)
{
	while (args[i])
	{
		if (ms_strcmp(args[i], ""))
			return (1);
		++i;
	}
	return (0);
}

static void	empty_norm(char **args, int i)
{
	char	*str;
	char	*tmp;

	while ((str = ft_strnstr(args[i], "echos empty argument :D",
						ft_strlen(args[i]))))
	{
		tmp = ft_substr(args[i], 0, str - args[i]);
		str = ft_substr(args[i], str - args[i] + 23, ft_strlen(str));
		free(args[i]);
		safe_strjoin(&tmp, str);
		free(str);
		args[i] = tmp;
	}
}

static void	print_args(char **args, int i)
{
	while (args[i])
	{
		if (ft_strnstr(args[i], "echos empty argument :D", ft_strlen(args[i])))
		{
			empty_norm(args, i);
			print_line(args[i], 1);
			++i;
			if (args_check(args, i))
				write(1, " ", 1);
			continue ;
		}
		print_line(args[i], 1);
		++i;
		if (!args[i])
			break ;
		if ((ms_strcmp(args[i - 1], "") && args_check(args, i)) ||
			ms_strcmp(args[i - 1], "echos empty argument :D"))
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
		while (args[i] && !ms_strcmp(args[i], "-n"))
			++i;
	}
	print_args(args, i);
	is_n_option(n_option);
	return (0);
}
