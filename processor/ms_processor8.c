/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processor8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:27:56 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/13 17:27:57 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_processor.h"

void		check_bslash(char *tmp, int *i, char **str, int *str_diff)
{
	if (tmp[*i + 1] == '\\')
	{
		ms_strswap(str, "\\", (*i - *str_diff), 1);
		++(*i);
	}
	else
		ms_strswap(str, "", (*i - *str_diff), 0);
	++(*str_diff);
	++(*i);
}

int			check_bslash2(char **str, int i)
{
	if ((*str)[i + 1] == '\\')
	{
		ms_strswap(str, "\\", i, 1);
		return (i);
	}
	else
		ms_strswap(str, "", i, 0);
	return (i);
}
