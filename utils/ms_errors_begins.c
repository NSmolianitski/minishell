/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors_begins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:48:39 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:48:41 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ms_utils.h"

void	write_ms_err_begin_with_cmd(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
}

void	write_ms_err_begin_export(char *str)
{
	write(2, "minishell: export: '", 20);
	print_line(str, 2);
	write(2, "': ", 3);
}

void	write_ms_err_begin_unset(char *str)
{
	write(2, "minishell: unset: '", 19);
	print_line(str, 2);
	write(2, "': ", 3);
}

void	write_ms_err_begin_exit(char *str)
{
	write(2, "minishell: exit: ", 17);
	print_line(str, 2);
	if (str)
		write(2, ": ", 2);
}

void	write_ms_err_begin_cd(char *str)
{
	write(2, "minishell: cd: ", 15);
	if (str[0] != '\0')
	{
		print_line(str, 2);
		write(2, ": ", 2);
	}
}
