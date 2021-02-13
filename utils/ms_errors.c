/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:46:36 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:46:38 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ms_utils.h"

static void	write_ms_err_begin(void)
{
	write(2, "minishell: ", 11);
}

void		print_error(char *error, char *str, int err_type)
{
	if (err_type == 1)
		write_ms_err_begin_with_cmd(str);
	else if (err_type == 2)
		write_ms_err_begin();
	else if (err_type == 3)
		write_ms_err_begin_export(str);
	else if (err_type == 4)
		write_ms_err_begin_cd(str);
	else if (err_type == 6)
		write_ms_err_begin_exit(str);
	else if (err_type == 7)
		write_ms_err_begin_unset(str);
	(!ms_strcmp(error, NSFD)) ? print_line(NSFD, 2) : 0;
	(!ms_strcmp(error, CNF)) ? print_line(CNF, 2) : 0;
	(!ms_strcmp(error, SES)) ? print_line(SES, 2) : 0;
	(!ms_strcmp(error, SEP)) ? print_line(SEP, 2) : 0;
	(!ms_strcmp(error, SEN)) ? print_line(SEN, 2) : 0;
	(!ms_strcmp(error, NVI)) ? print_line(NVI, 2) : 0;
	(!ms_strcmp(error, SNIP)) ? print_line(SNIP, 2) : 0;
	(!ms_strcmp(error, HNS)) ? print_line(HNS, 2) : 0;
	(!ms_strcmp(error, MLA)) ? print_line(MLA, 2) : 0;
	(!ms_strcmp(error, NAR)) ? print_line(NAR, 2) : 0;
	write(2, "\n", 1);
}
