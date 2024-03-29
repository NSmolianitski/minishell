/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:37:41 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:37:43 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"
#include "libft.h"

static void	clear_signal_symbols(void)
{
	write(1, "\b \b\b \b", ft_strlen("\b \b\b \b"));
}

void		sig_int(int sig)
{
	sig += 0;
	if (g_signal_flag != -1)
		clear_signal_symbols();
	write(1, "\n", 1);
	if (g_signal_flag != -1)
		print_shell_tag();
	g_signal_flag = sig;
}

void		sig_quit(int sig)
{
	sig += 0;
	if (g_signal_flag == -1)
	{
		write(1, "Quit: ", ft_strlen("Quit: "));
		ft_putnbr_fd(sig, 1);
		write(1, "\n", 1);
		g_exit_status = 131;
	}
	else
		clear_signal_symbols();
	g_signal_flag = sig;
}
