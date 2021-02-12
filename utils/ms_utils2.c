/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:54:19 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:54:20 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ms_utils.h"

/*
**  A function like strchr, but ignores content
**  in quotes, escaped $, but handles escaped quotes
*/

char	*ft_strchr_quotes(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && !is_symb_esc(s, i))
		{
			++i;
			while (s[i] != '\'' && s[i] != '\0')
				++i;
		}
		else if (s[i] == '"' && !is_symb_esc(s, i))
		{
			++i;
			while (s[i] != '"' && s[i] != '\0')
				++i;
		}
		if (s[i] == c)
			return ((char*)s + i);
		++i;
	}
	if (c == '\0')
		return ((char*)s + i);
	return (0);
}

/*
**  A function that swaps string part by coordinates
*/

int		ms_strswap(char **str, const char *inject, int start, int len)
{
	char	*result;
	char	*tmp;

	result = ft_substr(*str, 0, start);
	result = safe_strjoin(&result, inject);
	tmp = ft_substr(*str, start + 1 + len, ft_strlen(&(*str)[start + len]));
	result = safe_strjoin(&result, tmp);
	free(tmp);
	free(*str);
	*str = result;
	return (1);
}

/*
**  strchr with several symbols
*/

char	*ms_strmultichr(const char *s, const char *symbols)
{
	int		i;
	int		j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (symbols[j])
		{
			if (s[i] == symbols[j])
				return ((char *)s + i);
			++j;
		}
		++i;
	}
	return (0);
}

/*
**  strchr that skips escaped symbol
*/

char	*ms_bs_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			if (((i > 1 && !(s[i - 2] == '\\') && (s[i - 1] == '\\')) ||
					!(i > 0 && (s[i - 1] == '\\'))))
				return ((char *)s + i);
		++i;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (0);
}

/*
**  Function that makes free for two strings
*/

void	double_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
