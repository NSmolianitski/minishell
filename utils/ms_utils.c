/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:46:56 by pkentaur          #+#    #+#             */
/*   Updated: 2021/02/12 11:52:58 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "unistd.h"
#include "libft.h"

/*
**  A function that checks symbol escape
*/

int		is_symb_esc(const char *str, int i)
{
	if (i > 1)
	{
		if (str[i - 1] == '\\' && str[i - 2] == '\\')
			return (0);
		else if (str[i - 1] == '\\')
			return (1);
	}
	else if (i > 0)
		if (str[i - 1] == '\\')
			return (1);
	return (0);
}

/*
**  A function that skips spaces and return index of first non-space character
*/

int		skip_spaces(char const *line, int i)
{
	while (line[i] == ' ')
		++i;
	return (i);
}

char	*safe_strjoin(char **str1, const char *str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = ft_strjoin(*str1, str2);
	free(tmp);
	return (*str1);
}

/*
**  A function that prints string to fd
*/

int		print_line(char const *line, int fd)
{
	if (line == NULL)
		return (-1);
	write(fd, line, ft_strlen(line));
	return (0);
}

/*
**  A function that compares two strings and returns 0 if they are equal
*/

int		ms_strcmp(const char *s1, const char *s2)
{
	unsigned int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			if ((((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]) > 0)
				return (1);
			else
				return (-1);
		}
		++i;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-1);
}
